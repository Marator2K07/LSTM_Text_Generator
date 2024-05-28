#ifndef SOFTMAXCROSSENTROPYLOSS_H
#define SOFTMAXCROSSENTROPYLOSS_H

#include "iloss.h"

///
/// \brief The SoftmaxCrossEntropyLoss class
/// перекрестно-энтропийная потеря
class SoftmaxCrossEntropyLoss : ILoss
{
private:
    // ILoss interface
    double calculate() override;
    Matrix *inputGradient() override;

public:
    SoftmaxCrossEntropyLoss();    

public:
    // ILoss interface
    double forward(Matrix *prediction, Matrix *target) override;
    Matrix *backward() override;
};

#endif // SOFTMAXCROSSENTROPYLOSS_H
