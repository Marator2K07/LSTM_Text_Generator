#ifndef LSTMNODE_H
#define LSTMNODE_H

#include "ineuralnetworknode.h"

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
    forward(QMap<QString, Matrix2d<double>> input,
            QMap<QString, QMap<QString, Matrix2d<double>>> &layerParams) override;
    QMap<QString, Matrix2d<double>>
    backward(QMap<QString, Matrix2d<double>> outputGrad,
             QMap<QString, QMap<QString, Matrix2d<double>>> &layerParams) override;
    //

};

#endif // LSTMNODE_H
