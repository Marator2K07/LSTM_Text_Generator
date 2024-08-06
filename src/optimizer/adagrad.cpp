#include "adagrad.h"

void AdaGrad::initSumSquares()
{
    int layerIndex = 0;
    for (INeuralNetworkLayer *layer : _model->layers()) {
        _sumSquares.push_back(QMap<QString, Matrix2d<double>>());
        const QList<QString> layerKeys = layer->params().keys();
        for (const QString &key : layerKeys) {
            // ради удобства определяем первичный параметр слоя
            QMap<QString, Matrix2d<double>> currentParam
                = layer->params().value(key);
            // сама инициализация
            _sumSquares[layerIndex].insert(
                key,
                Matrix2d<double>::zeroM(
                    currentParam["value"].sizes()[0],
                    currentParam["value"].sizes()[1]
                    )
                );
        }
        layerIndex++;
    }
    _first = false;
}

AdaGrad::AdaGrad(INeuralNetworkModel *model,
                 double learningRate,
                 double epsilon,
                 bool gradientClip)
    : _model{model}
    , _learningRate{learningRate}
    , _epsilon{epsilon}
    , _gradientClip{gradientClip}
    , _first{true}
{
}

OptimizerType AdaGrad::type() const
{
    return OptimizerType::ADA_GRAD;
}

double AdaGrad::learningRate() const
{
    return _learningRate;
}

void AdaGrad::newLearningRate(const double learningRate)
{
    _learningRate = learningRate;
}

void AdaGrad::update()
{
    // при первом проходе инициализируем словарь хранения суммы
    // квадратов градиентов для каждого параметра каждого слоя
    if (_first) {
        initSumSquares();
    }
    // каждого параметра каждого слоя
    int layerIndex = 0;
    for (INeuralNetworkLayer *layer : _model->layers()) {
        const QList<QString> layerKeys = layer->params().keys();
        for (const QString &key : layerKeys) {
            // ради удобства определяем первичный параметр слоя
            QMap<QString, Matrix2d<double>> currentParam
                = layer->params().value(key);
            // если включена обрезка градиентов
            if (_gradientClip) {
                layer->updateParam(
                    key,
                    "deriv",
                    Matrix2d<double>(
                        currentParam["deriv"].clipM(-1.45, 1.45)
                        )
                    );
            }
            // вычисление новой суммы квадратов градиента
            Matrix2d<double> newSumSquare(
                currentParam["deriv"]
                    .simplifiedMult(&currentParam["deriv"])
                    ->addition(_epsilon)
                );
            _sumSquares[layerIndex].insert(
                key,
                Matrix2d<double>(
                    _sumSquares[layerIndex].value(key)
                        .addition(&newSumSquare)
                    )
                );
            // масштабирование скорости обучения
            Matrix2d<double> learningRateMatrix(
                _sumSquares[layerIndex].value(key)
                    .sqrtM()
                    ->dividing(_learningRate, true)
                );
            // обновление параметра сети
            Matrix2d<double> newValue(
                currentParam["value"]
                    .subtraction(
                        learningRateMatrix.simplifiedMult(&currentParam["deriv"]).get()
                        )
                );
            layer->updateParam(key, "value", newValue);
        }
        layerIndex++;
    }
}
