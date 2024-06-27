#include "lstmmodel.h"
#include "matrix3d.cpp"

LSTMModel::LSTMModel(ILoss *loss, QList<INeuralNetworkLayer *> layers)
    : _loss{loss}
    , _layers{layers}
{
}

QList<INeuralNetworkLayer *> LSTMModel::layers() const
{
    return _layers;
}

Matrix3d<double> LSTMModel::forward(Matrix3d<double> batch)
{
    Matrix3d<double> predictionBatch;
    // обрабатываем входящие значения в предсказание сети
    for (INeuralNetworkLayer *layer : _layers) {
        predictionBatch = layer->forward(batch);
    }

    return predictionBatch;
}

Matrix3d<double> LSTMModel::backward(Matrix3d<double> gradient)
{
    Matrix3d<double> lossGradient;
    // обрабатываем градиент в обратном порядке
    for (int i = _layers.size()-1; i >= 0; --i) {
        _layers.value(i)->backward(gradient);
    }

    return lossGradient;
}

double LSTMModel::singleStep(Matrix3d<double> xBatch,
                             Matrix3d<double> yBatch)
{
    // 1) находим предсказание сети (прямой проход)
    Matrix3d<double> xBatchPrediction = forward(xBatch);
    // 2) высчитываем среднюю квадратичную потерю и градиент потерь
    double meanLoss = _loss->forward(&xBatchPrediction, &yBatch);
    Matrix3d<double> lossGradient(_loss->backward());
    // 3) чистка градиентов
    for (INeuralNetworkLayer *layer : _layers) {
        layer->clearGradients();
    }
    // 4) обратный проход (обновление параметров сети)
    backward(lossGradient);

    return meanLoss;
}
