#include "lstmlayer.h"

LSTMLayer::LSTMLayer(int hiddenSize, int outputSize, double weightScale)
    : _hiddenSize{hiddenSize}
    , _outputSize{outputSize}
    , _weightScale{weightScale}
{
    _startH = Matrix2d<double>::zeroM(1, hiddenSize);
    _startC = Matrix2d<double>::zeroM(1, hiddenSize);
    _firstStep = true;
}

void LSTMLayer::initParams(const Matrix3d<double> initMatrix)
{
    _vocabSize = initMatrix.sizes()[2];
    // преинициализация параметров слоя
    _params.insert("W_f", QMap<QString, Matrix2d<double>>());
    _params.insert("B_f", QMap<QString, Matrix2d<double>>());
    _params.insert("W_i", QMap<QString, Matrix2d<double>>());
    _params.insert("B_i", QMap<QString, Matrix2d<double>>());
    _params.insert("W_c", QMap<QString, Matrix2d<double>>());
    _params.insert("B_c", QMap<QString, Matrix2d<double>>());
    _params.insert("W_o", QMap<QString, Matrix2d<double>>());
    _params.insert("B_o", QMap<QString, Matrix2d<double>>());
    _params.insert("W_v", QMap<QString, Matrix2d<double>>());
    _params.insert("B_v", QMap<QString, Matrix2d<double>>());
    // инициализация значений параметров слоя
    _params["W_f"].insert(
        "value",
        Matrix2d<double>::randomNormal(0.0, _weightScale,
                                       _hiddenSize+_vocabSize, _hiddenSize)
        );
    _params["B_f"].insert(
        "value",
        Matrix2d<double>::randomNormal(0.0, _weightScale, 1, _hiddenSize)
        );
    _params["W_i"].insert(
        "value",
        Matrix2d<double>::randomNormal(0.0, _weightScale,
                                       _hiddenSize+_vocabSize, _hiddenSize)
        );
    _params["B_i"].insert(
        "value",
        Matrix2d<double>::randomNormal(0.0, _weightScale, 1, _hiddenSize)
        );
    _params["W_c"].insert(
        "value",
        Matrix2d<double>::randomNormal(0.0, _weightScale,
                                       _hiddenSize+_vocabSize, _hiddenSize)
        );
    _params["B_c"].insert(
        "value",
        Matrix2d<double>::randomNormal(0.0, _weightScale, 1, _hiddenSize)
        );
    _params["W_o"].insert(
        "value",
        Matrix2d<double>::randomNormal(0.0, _weightScale,
                                       _hiddenSize+_vocabSize, _hiddenSize)
        );
    _params["B_o"].insert(
        "value",
        Matrix2d<double>::randomNormal(0.0, _weightScale, 1, _hiddenSize)
        );
    _params["W_v"].insert(
        "value",
        Matrix2d<double>::randomNormal(0.0, _weightScale,
                                       _hiddenSize, _outputSize)
        );
    _params["B_v"].insert(
        "value",
        Matrix2d<double>::randomNormal(0.0, _weightScale, 1, _outputSize)
        );
    // инициализация производных параметров слоя
    const QList<QString> keys = _params.keys();
    for (const QString &key : keys) {
        _params[key].insert(
            "deriv",
            Matrix2d<double>::zeroM(
                _params[key]["value"].sizes()[0],
                _params[key]["value"].sizes()[1])
            );
    }
    // инициализируем ячейки для нейронов/узлов
    for (int i = 0; i < initMatrix.sizes()[1]; ++i) {
        _cells.push_back(LSTMNode());
    }
    // сбрасываем флаг инициализации
    _firstStep = false;
}

void LSTMLayer::clearGradients()
{
    // обнуление производных параметров слоя
    const QList<QString> keys = _params.keys();
    for (const QString &key : keys) {
        _params[key]["deriv"]
            = Matrix2d<double>::zeroM(_params[key]["deriv"].sizes()[0],
                                      _params[key]["deriv"].sizes()[1]);
    }
}

Matrix3d<double> LSTMLayer::forward(Matrix3d<double> xSequenceIn)
{
    // если проходим впервые
    if (_firstStep) {
        initParams(xSequenceIn);
    }
    try {
        // устанавливаем размер пакет/партии
        unsigned long long batchSize = xSequenceIn.sizes()[0];
        // копии начального скрытого состояния и ячейки памяти
        Matrix2d<double> hIn(_startH.data());
        Matrix2d<double> cIn(_startC.data());
        // повторяем копии batchSize раз ради соотвествия по размеру/ам
        hIn = Matrix2d<double>(hIn.rowsRepeat(batchSize)->data());
        cIn = Matrix2d<double>(cIn.rowsRepeat(batchSize)->data());
        // находим длину последовательности и подготавливаем основу выхода слоя
        unsigned long long sequenceLength = xSequenceIn.sizes()[1];
        Matrix3d<double> xSequenceOut
            = Matrix3d<double>::zeroM(batchSize, sequenceLength, _outputSize);
        // для каждого временного шага:
        // 1) извлекается входная матрица значений
        // 2) прямой проход через узел/ячейку сети
        // 3) обновление матрицы значений и состояний
        for (int t = 0; t < sequenceLength; ++t) {
            Matrix2d<double> xIn = xSequenceIn.rowsWithIndex(t);
            QMap<QString, Matrix2d<double>> out
                = _cells[t].forward(xIn, hIn, cIn, _params);
            hIn = out["H_out"];
            cIn = out["C_out"];
            xSequenceOut.setRowsWithIndex(out["X_out"], t);
        }
        // в итоге обновляется и стартовое скрытое состояние сети и ячейки
        _startH = Matrix2d<double>(hIn.axisMean(0)->data());
        _startC = Matrix2d<double>(cIn.axisMean(0)->data());

        return xSequenceOut;
    } catch (const MatrixException &e) {
        cout << e.what() << endl;
    }

}

Matrix3d<double> LSTMLayer::backward(Matrix3d<double> xSequenceOutGrad)
{
    try {
        // устанавливаем размер пакет/партии
        unsigned long long batchSize = xSequenceOutGrad.sizes()[0];
        // подготавливаем матрицы входа градиента для
        // скрытого состояния и состояния ячейки
        Matrix2d<double> hInGrad = Matrix2d<double>::zeroM(batchSize, _hiddenSize);
        Matrix2d<double> cInGrad = Matrix2d<double>::zeroM(batchSize, _hiddenSize);
        // задаем количество символов для обработки
        unsigned long long numChars = xSequenceOutGrad.sizes()[1];
        // подготавливаем основу для хранения входных градиентов данных
        Matrix3d<double> xSequenceInGrad
            = Matrix3d<double>::zeroM(batchSize, numChars, _vocabSize);
        // во время обратного прохода для каждого символа(временной шаг t):
        // 1) извлекается градиент для текущего символа
        // 2) обратный проход через узел/ячейку сети
        // 3) обновление градиентов данных и состояний сети, ячеек
        for (int t = numChars-1; t >= 0; --t) {
            Matrix2d<double> xInGrad = xSequenceOutGrad.rowsWithIndex(t);
            QMap<QString, Matrix2d<double>> inGrad
                = _cells[t].backward(xInGrad, hInGrad, cInGrad, _params);
            hInGrad = inGrad["dH_prev"];
            cInGrad = inGrad["dC_prev"];
            xSequenceInGrad.setRowsWithIndex(inGrad["dX_prev"], t);
        }

        return xSequenceInGrad;
    } catch (const MatrixException &e) {
        cout << e.what() << endl;
    }
}
