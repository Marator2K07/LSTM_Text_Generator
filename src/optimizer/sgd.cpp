#include "sgd.h"

SGD::SGD(INeuralNetworkModel *model,
         double learningRate,
         bool gradientClip)
    : _model{model}
    , _learningRate{learningRate}
    , _gradientClip{gradientClip}
{
}

OptimizerType SGD::type() const
{
    return OptimizerType::SGD;
}

double SGD::learningRate() const
{
    return _learningRate;
}

void SGD::newLearningRate(const double learningRate)
{
    _learningRate = learningRate;
}

void SGD::update()
{
    // каждого параметра каждого слоя
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
                        currentParam["deriv"].clipM(-1.5, 1.5)
                        )
                    );
            }
            // получаем обновленное значение градиента
            Matrix2d<double> updateGrad(
                currentParam["deriv"].multiplication(_learningRate)
                );
            // обновляем параметр сети
            Matrix2d<double> newValue(
                currentParam["value"].subtraction(&updateGrad)
                );
            layer->updateParam(key, "value", newValue);
        }
    }
}
