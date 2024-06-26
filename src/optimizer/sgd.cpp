#include "sgd.h"
#include "matrix2d.cpp"

SGD::SGD(INeuralNetworkModel *model,
         double learningRate,
         bool gradientClip)
    : _model{model}
    , _learningRate{learningRate}
    , _gradientClip{gradientClip}
{
}

void SGD::update()
{
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
                        currentParam["deriv"].clipM(-2, 2)->data()
                        )
                    );
            }
            // получаем обновленное значение градиента
            Matrix2d<double> updateGrad(
                currentParam["deriv"].multiplication(_learningRate)->data()
                );
            // обновляем параметр сети
            Matrix2d<double> newValue(currentParam["value"].subtraction(&updateGrad)->data());
            layer->updateParam(
                key,
                "value",
                newValue
                );
        }
    }
}
