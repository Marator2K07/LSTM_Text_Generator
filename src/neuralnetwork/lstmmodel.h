#ifndef LSTMMODEL_H
#define LSTMMODEL_H

#include "ineuralnetworkmodel.h"

///
/// \brief The LSTMModel class
/// модель нейронной сети типа LSTM
class LSTMModel : public INeuralNetworkModel
{
private:
    ILoss *_loss; // интерфейс вычисления потерь
    QList<INeuralNetworkLayer *> _layers; // список слоев модели

public:
    LSTMModel(ILoss *loss, QList<INeuralNetworkLayer *> layers);

public:
    // INeuralNetworkModel interface
    QList<INeuralNetworkLayer *> layers() const override;
    Matrix3d<double> forward(Matrix3d<double> batch) override;
    Matrix3d<double> backward(Matrix3d<double> gradient) override;
    double singleStep(Matrix3d<double> xBatch,
                      Matrix3d<double> yBatch) override;
    //

};

#endif // LSTMMODEL_H
