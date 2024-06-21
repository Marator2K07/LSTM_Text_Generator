#include "lstmlayer.h"

LSTMLayer::LSTMLayer(int hiddenSize, int outputSize, double weightScale)
    : _hiddenSize{hiddenSize}
    , _outputSize{outputSize}
    , _weightScale{weightScale}
{
    _startH = Matrix2d<double>::zeroM(1, hiddenSize);
    _startC = Matrix2d<double>::zeroM(1, hiddenSize);
    _firstStep = true;
}

void LSTMLayer::initParams(const Matrix3d<double> initMatrix)
{

}

void LSTMLayer::clearGradients()
{

}

Matrix3d<double> LSTMLayer::forward(Matrix3d<double> xSequenceIn)
{

}

Matrix3d<double> LSTMLayer::backward(Matrix3d<double> xSequenceOutGrad)
{

}
