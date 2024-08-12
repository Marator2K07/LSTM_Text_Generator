#include "lstmlayer.h"
#include "matrix2d.cpp"
#include "matrix3d.cpp"

void LSTMLayer::saveHyperParams(const QString path)
{
    // подготовка
    QString fileName = QString("%1/%2.txt").arg(path, _name);
    ofstream file;
    // пытаемся открыть файл
    file.open(fileName.toStdString());
    if (!file.is_open()) {
        throw MatrixException(
            QString("Catch neural network layer saving hyperparams exception:\n[%1]\n")
                .arg("Failed to open file")
            );
    }
    // пишем гиперпараметры в файл
    file << _hiddenSize << " " << _outputSize << " " << _vocabSize << " "
         << _sequenceSize << " " << _weightScale << " ";

    file.close();
}

void LSTMLayer::loadHyperParams(const QString path)
{
    // подготовка
    QString fileName = QString("%1/%2.txt").arg(path, _name);
    ifstream file;
    // пытаемся открыть файл
    file.open(fileName.toStdString());
    if (!file.is_open()) {
        throw MatrixException(
            QString("Catch neural network layer loading hyperparams exception:\n[%1]\n")
                .arg("Failed to open file")
            );
    }
    // считываем гиперпараметры
    string line;
    getline(file, line);
    istringstream rowStream(line);
    rowStream >> _hiddenSize >> _outputSize >> _vocabSize
        >> _sequenceSize >> _weightScale;

    cout << _hiddenSize << endl;
    cout << _outputSize << endl;
    cout << _vocabSize << endl;
    cout << _sequenceSize << endl;
    cout << _weightScale << endl;

    file.close();
}

LSTMLayer::LSTMLayer(QString name, int hiddenSize, int outputSize, double weightScale)
    : _name{name}
    , _hiddenSize{hiddenSize}
    , _outputSize{outputSize}
    , _weightScale{weightScale}
{
    _startH = Matrix2d<double>::zeroM(1, hiddenSize);
    _startC = Matrix2d<double>::zeroM(1, hiddenSize);
    _firstStep = true;
}

LSTMLayer::LSTMLayer(const QString path, const QString layerName)
    : _name{layerName}
{
    loadParams(path);
}

LSTMLayer::~LSTMLayer()
{
}

QString LSTMLayer::name() const
{
    return _name;
}

int LSTMLayer::power() const
{
    // пусть мощность слоя выражается как произведение
    // всех параметров, влияющих на "тяжеловесность" слоя
    return _hiddenSize * _outputSize * _vocabSize * _sequenceSize;
}

bool LSTMLayer::compareLayer(INeuralNetworkLayer *layer)
{
    // сравниваем все значения
    if (!_params["W_f"]["value"].compareDoubles(layer->paramAt("W_f", "value"), 1e-5)) {
        return false;
    }
    if (!_params["W_i"]["value"].compareDoubles(layer->paramAt("W_i", "value"), 1e-5)) {
        return false;
    }
    if (!_params["W_c"]["value"].compareDoubles(layer->paramAt("W_c", "value"), 1e-5)) {
        return false;
    }
    if (!_params["W_o"]["value"].compareDoubles(layer->paramAt("W_o", "value"), 1e-5)) {
        return false;
    }
    if (!_params["W_v"]["value"].compareDoubles(layer->paramAt("W_v", "value"), 1e-5)) {
        return false;
    }
    if (!_params["B_f"]["value"].compareDoubles(layer->paramAt("B_f", "value"), 1e-5)) {
        return false;
    }
    if (!_params["B_i"]["value"].compareDoubles(layer->paramAt("B_i", "value"), 1e-5)) {
        return false;
    }
    if (!_params["B_c"]["value"].compareDoubles(layer->paramAt("B_c", "value"), 1e-5)) {
        return false;
    }
    if (!_params["B_o"]["value"].compareDoubles(layer->paramAt("B_o", "value"), 1e-5)) {
        return false;
    }
    if (!_params["B_v"]["value"].compareDoubles(layer->paramAt("B_v", "value"), 1e-5)) {
        return false;
    }
    // сравниваем все градиенты
    if (!_params["W_f"]["deriv"].compareDoubles(layer->paramAt("W_f", "deriv"), 1e-5)) {
        return false;
    }
    if (!_params["W_i"]["deriv"].compareDoubles(layer->paramAt("W_i", "deriv"), 1e-5)) {
        return false;
    }
    if (!_params["W_c"]["deriv"].compareDoubles(layer->paramAt("W_c", "deriv"), 1e-5)) {
        return false;
    }
    if (!_params["W_o"]["deriv"].compareDoubles(layer->paramAt("W_o", "deriv"), 1e-5)) {
        return false;
    }
    if (!_params["W_v"]["deriv"].compareDoubles(layer->paramAt("W_v", "deriv"), 1e-5)) {
        return false;
    }
    if (!_params["B_f"]["deriv"].compareDoubles(layer->paramAt("B_f", "deriv"), 1e-5)) {
        return false;
    }
    if (!_params["B_i"]["deriv"].compareDoubles(layer->paramAt("B_i", "deriv"), 1e-5)) {
        return false;
    }
    if (!_params["B_c"]["deriv"].compareDoubles(layer->paramAt("B_c", "deriv"), 1e-5)) {
        return false;
    }
    if (!_params["B_o"]["deriv"].compareDoubles(layer->paramAt("B_o", "deriv"), 1e-5)) {
        return false;
    }
    if (!_params["B_v"]["deriv"].compareDoubles(layer->paramAt("B_v", "deriv"), 1e-5)) {
        return false;
    }
    // если дошли до сюда, то все успешно
    return true;
}

Matrix2d<double> LSTMLayer::paramAt(const QString firstKey, const QString secondKey) const
{
    return _params[firstKey][secondKey];
}

void LSTMLayer::updateParam(const QString firstKey,
                            const QString secondKey,
                            const Matrix2d<double> value)
{
    _params[firstKey].insert(secondKey, value);
}

void LSTMLayer::saveParams(const QString path)
{
    try {
        // сначала сохраняем гиперпараметры
        saveHyperParams(path);
        // собираем основной путь
        QString fullPath = QString("%1/%2_").arg(path, _name);
        // сохраняем все значения
        _params["W_f"]["value"].saveToFile(fullPath + "W_f_value.txt");
        _params["W_i"]["value"].saveToFile(fullPath + "W_i_value.txt");
        _params["W_c"]["value"].saveToFile(fullPath + "W_c_value.txt");
        _params["W_o"]["value"].saveToFile(fullPath + "W_o_value.txt");
        _params["W_v"]["value"].saveToFile(fullPath + "W_v_value.txt");
        _params["B_f"]["value"].saveToFile(fullPath + "B_f_value.txt");
        _params["B_i"]["value"].saveToFile(fullPath + "B_i_value.txt");
        _params["B_c"]["value"].saveToFile(fullPath + "B_c_value.txt");
        _params["B_o"]["value"].saveToFile(fullPath + "B_o_value.txt");
        _params["B_v"]["value"].saveToFile(fullPath + "B_v_value.txt");
        // сохраняем все градиенты
        _params["W_f"]["deriv"].saveToFile(fullPath + "W_f_deriv.txt");
        _params["W_i"]["deriv"].saveToFile(fullPath + "W_i_deriv.txt");
        _params["W_c"]["deriv"].saveToFile(fullPath + "W_c_deriv.txt");
        _params["W_o"]["deriv"].saveToFile(fullPath + "W_o_deriv.txt");
        _params["W_v"]["deriv"].saveToFile(fullPath + "W_v_deriv.txt");
        _params["B_f"]["deriv"].saveToFile(fullPath + "B_f_deriv.txt");
        _params["B_i"]["deriv"].saveToFile(fullPath + "B_i_deriv.txt");
        _params["B_c"]["deriv"].saveToFile(fullPath + "B_c_deriv.txt");
        _params["B_o"]["deriv"].saveToFile(fullPath + "B_o_deriv.txt");
        _params["B_v"]["deriv"].saveToFile(fullPath + "B_v_deriv.txt");
        // сохраняем начальные состояния
        _startH.saveToFile(fullPath + "H_start.txt");
        _startC.saveToFile(fullPath + "C_start.txt");
    } catch (const MatrixException &e) {
        throw NeuralNetworkException(
            QString("Catch neural network params saving exception:\n[%1]\n")
                .arg(e.what())
            );
    } catch (const NeuralNetworkException &e) {
        throw NeuralNetworkException(
            QString("Catch neural network params saving exception:\n[%1]\n")
                .arg(e.what())
            );
    }
}

void LSTMLayer::loadParams(const QString path)
{
    try {
        // сначала загружаем гиперпараметры
        loadHyperParams(path);
        // собираем основной путь
        QString fullPath = QString("%1/%2_").arg(path, _name);
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
        // загружаем все значения
        _params["W_f"]["value"].loadFromFile(fullPath + "W_f_value.txt");
        _params["W_i"]["value"].loadFromFile(fullPath + "W_i_value.txt");
        _params["W_c"]["value"].loadFromFile(fullPath + "W_c_value.txt");
        _params["W_o"]["value"].loadFromFile(fullPath + "W_o_value.txt");
        _params["W_v"]["value"].loadFromFile(fullPath + "W_v_value.txt");
        _params["B_f"]["value"].loadFromFile(fullPath + "B_f_value.txt");
        _params["B_i"]["value"].loadFromFile(fullPath + "B_i_value.txt");
        _params["B_c"]["value"].loadFromFile(fullPath + "B_c_value.txt");
        _params["B_o"]["value"].loadFromFile(fullPath + "B_o_value.txt");
        _params["B_v"]["value"].loadFromFile(fullPath + "B_v_value.txt");
        // загружаем все градиенты
        _params["W_f"]["deriv"].loadFromFile(fullPath + "W_f_deriv.txt");
        _params["W_i"]["deriv"].loadFromFile(fullPath + "W_i_deriv.txt");
        _params["W_c"]["deriv"].loadFromFile(fullPath + "W_c_deriv.txt");
        _params["W_o"]["deriv"].loadFromFile(fullPath + "W_o_deriv.txt");
        _params["W_v"]["deriv"].loadFromFile(fullPath + "W_v_deriv.txt");
        _params["B_f"]["deriv"].loadFromFile(fullPath + "B_f_deriv.txt");
        _params["B_i"]["deriv"].loadFromFile(fullPath + "B_i_deriv.txt");
        _params["B_c"]["deriv"].loadFromFile(fullPath + "B_c_deriv.txt");
        _params["B_o"]["deriv"].loadFromFile(fullPath + "B_o_deriv.txt");
        _params["B_v"]["deriv"].loadFromFile(fullPath + "B_v_deriv.txt");
        // загружаем начальные состояния
        _startH.loadFromFile(fullPath + "H_start.txt");
        _startC.loadFromFile(fullPath + "C_start.txt");
        // инициализируем ячейки для нейронов/узлов
        for (int i = 0; i < _sequenceSize; ++i) { /// ПОТОМ УБРАТЬ ХАРДКОД
            _cells.push_back(new LSTMNode());
        }
        // сбрасываем метку первой инициализации
        _firstStep = false;
    } catch (const MatrixException &e) {
        throw NeuralNetworkException(
            QString("Catch neural network params loading exception:\n[%1]\n")
                .arg(e.what())
            );
    } catch (const NeuralNetworkException &e) {
        throw NeuralNetworkException(
            QString("Catch neural network params loading exception:\n[%1]\n")
                .arg(e.what())
            );
    }
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
    _sequenceSize = initMatrix.sizes()[1];
    for (int i = 0; i < _sequenceSize; ++i) {
        _cells.push_back(new LSTMNode());
    }
    // сбрасываем флаг инициализации
    _firstStep = false;
}

QMap<QString, QMap<QString, Matrix2d<double>>> LSTMLayer::params() const
{
    return _params;
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
    try {
        // если проходим впервые
        if (_firstStep) {
            initParams(xSequenceIn);
        }
        // устанавливаем размер пакет/партии
        unsigned long long batchSize = xSequenceIn.sizes()[0];
        // копии начального скрытого состояния и ячейки памяти
        Matrix2d<double> hIn(_startH.data());
        Matrix2d<double> cIn(_startC.data());
        // повторяем копии batchSize раз ради соотвествия по размеру/ам
        hIn = Matrix2d<double>(hIn.rowsRepeat(batchSize));
        cIn = Matrix2d<double>(cIn.rowsRepeat(batchSize));
        // находим длину последовательности и подготавливаем основу выхода слоя
        unsigned long long sequenceLength = xSequenceIn.sizes()[1];
        Matrix3d<double> xSequenceOut
            = Matrix3d<double>::zeroM(batchSize, sequenceLength, _outputSize);
        // для каждого временного шага:
        // 1) извлекается входная матрица значений
        // 2) прямой проход через узел/ячейку сети
        // 3) обновление матрицы значений и состояний
        for (unsigned long long t = 0; t < sequenceLength; ++t) {
            Matrix2d<double> xIn = xSequenceIn.rowsWithIndex(t);
            QMap<QString, Matrix2d<double>> out
                = _cells[t]->forward(xIn, hIn, cIn, _params);
            hIn = out["H_out"];
            cIn = out["C_out"];
            xSequenceOut.setRowsWithIndex(out["X_out"], t);
        }
        // в итоге обновляется и стартовое скрытое состояние сети и ячейки
        _startH = Matrix2d<double>(hIn.axisMean(0));
        _startC = Matrix2d<double>(cIn.axisMean(0));

        return xSequenceOut;
    } catch (const MatrixException &e) {
        throw NeuralNetworkException(
            QString("\nNeural network exception \n[%1]<-[%2]\n")
                .arg("Error in forward layer pass", e.what())
            );
    } catch (const exception &e) {
        throw NeuralNetworkException(
            QString("\nNeural network exception \n[%1]<-[%2]\n")
                .arg("Error in backward layer pass", e.what())
            );
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
        long long t = numChars-1;
        do {
            Matrix2d<double> xInGrad = xSequenceOutGrad.rowsWithIndex(t);
            QMap<QString, Matrix2d<double>> inGrad
                = _cells[t]->backward(xInGrad, hInGrad, cInGrad, _params);
            hInGrad = inGrad["dH_prev"];
            cInGrad = inGrad["dC_prev"];
            xSequenceInGrad.setRowsWithIndex(inGrad["dX_prev"], t);
            t--;
        } while (t >= 0);

        return xSequenceInGrad;
    } catch (const MatrixException &e) {
        throw NeuralNetworkException(
            QString("\nNeural network exception \n[%1]<-[%2]\n")
                .arg("Error in backward layer pass", e.what())
            );
    } catch (const exception &e) {
        throw NeuralNetworkException(
            QString("\nNeural network exception \n[%1]<-[%2]\n")
                .arg("Error in backward layer pass", e.what())
            );
    }
}
