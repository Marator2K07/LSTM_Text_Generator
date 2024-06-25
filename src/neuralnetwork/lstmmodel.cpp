#include "lstmmodel.h"

LSTMModel::LSTMModel(ILoss *loss, QList<INeuralNetworkLayer *> layers)
    : _loss{loss}
    , _layers{layers}
{
}

Matrix3d<double> LSTMModel::forward(Matrix3d<double> batch)
{

}

Matrix3d<double> LSTMModel::backward(Matrix3d<double> gradient)
{

}

double LSTMModel::singleStep(Matrix3d<double> xBatch,
                             Matrix3d<double> yBatch)
{

}
