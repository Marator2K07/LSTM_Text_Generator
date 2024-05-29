#ifndef SOFTMAXCROSSENTROPYLOSS_H
#define SOFTMAXCROSSENTROPYLOSS_H

#include "iloss.h"
#include "activationfunctions.h"

///
/// \brief The SoftmaxCrossEntropyLoss class
/// перекрестно-энтропийная потеря
class SoftmaxCrossEntropyLoss : ILoss
{
private:
    double stabBorder; // стабилизирующая граница для вывода softmax
    vector<vector<double>> _prediction;
    vector<vector<double>> _target;

private:
    // ILoss interface
    double calculate() override;
    vector<vector<double>> inputGradient() override;

public:
    SoftmaxCrossEntropyLoss(double stabBorder = 1e-9);

public:
    // ILoss interface
    double forward(vector<vector<double>> prediction,
                   vector<vector<double>> target) override;
    vector<vector<double>> backward() override;
};

#endif // SOFTMAXCROSSENTROPYLOSS_H
