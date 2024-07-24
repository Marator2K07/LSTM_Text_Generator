#ifndef SOFTMAXCROSSENTROPYLOSS_H
#define SOFTMAXCROSSENTROPYLOSS_H

#include "iloss.h"

///
/// \brief The SoftmaxCrossEntropyLoss class
/// перекрестно-энтропийная потеря
class SoftmaxCrossEntropyLoss : public ILoss
{
private:
    double _stabBorder; // стабилизирующая граница для вывода softmax
    IMatrix<double> *_prediction;
    IMatrix<double> *_target;
    IMatrix<double> *_softmaxPrediction; // предсказания в пределах [0,1]
    IMatrix<double> *_inputGradient; // градиент для входных данных

private:
    // ILoss interface
    double calcLoss() override;
    IMatrix<double> *calcInputGradient() override;

public:
    SoftmaxCrossEntropyLoss(double stabBorder = 1e-9);
    ~SoftmaxCrossEntropyLoss();

public:
    // ILoss interface
    double forward(IMatrix<double> *prediction,
                   IMatrix<double> *target) override;
    unique_ptr<IMatrix<double>> backward() override;
};

#endif // SOFTMAXCROSSENTROPYLOSS_H
