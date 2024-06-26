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

}
