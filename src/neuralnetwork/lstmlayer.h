#ifndef LSTMLAYER_H
#define LSTMLAYER_H

#include "ineuralnetworklayer.h"
#include "matrix2d.cpp"

class LSTMLayer : public INeuralNetworkLayer
{
public:
    LSTMLayer();

public:
    // INeuralNetworkLayer interface
    void initParams(const Matrix3d<double> initMatrix) override;
    void clearGradients() override;
    Matrix3d<double> forward(Matrix3d<double> xSequenceIn) override;
    Matrix3d<double> backward(Matrix3d<double> xSequenceOutGrad) override;
    //

};

#endif // LSTMLAYER_H
