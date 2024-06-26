#ifndef LSTMNODE_H
#define LSTMNODE_H

#include "ineuralnetworknode.h"

///
/// \brief The LSTMNode class
/// узла нейронной сети типа LSTM
class LSTMNode : public INeuralNetworkNode
{
private:
    // сохраненные значения после прямого прохода
    QMap<QString, Matrix2d<double>> _forwardPassValues;

public:
    LSTMNode();

public:
    // INeuralNetworkNode interface
    QMap<QString, Matrix2d<double>>
    forward(Matrix2d<double> xIn,
            Matrix2d<double> hIn,
            Matrix2d<double> cIn,
            QMap<QString, QMap<QString, Matrix2d<double>>> &layerParams) override;
    QMap<QString, Matrix2d<double>>
    backward(Matrix2d<double> xOutGrad,
             Matrix2d<double> hOutGrad,
             Matrix2d<double> cOutGrad,
             QMap<QString, QMap<QString, Matrix2d<double>>> &layerParams) override;
    //

};

#endif // LSTMNODE_H
