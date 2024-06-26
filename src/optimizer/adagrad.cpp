#include "adagrad.h"

AdaGrad::AdaGrad(INeuralNetworkModel *model,
                 double learningRate,
                 bool gradientClip)
    : _model{model}
    , _learningRate{learningRate}
    , _gradientClip{gradientClip}
{
}

void AdaGrad::update()
{
    // при первом проходе инициализируем словарь хранения суммы
    // квадратов градиентов для каждого параметра каждого слоя
    if (_first) {
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
}
