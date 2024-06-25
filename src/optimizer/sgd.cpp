#include "sgd.h"

SGD::SGD(double learningRate, bool gradientClip)
    : _learningRate{learningRate}
    , _gradientClip{gradientClip}
{
}

void SGD::updateRule(QMap<QString, Matrix2d<double>> &stepParams)
{

}

void SGD::step()
{

}
