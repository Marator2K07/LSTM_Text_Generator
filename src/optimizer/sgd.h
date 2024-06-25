#ifndef SGD_H
#define SGD_H

#include "ioprimizer.h"

///
/// \brief The SGD class
/// оптимизатор нейронной сети Stochastic Gradient Descent
/// (стохастический градиентный спуск)
class SGD : public IOprimizer
{
private:
    INeuralNetworkModel *_model; // модель нейронной сети
    double _learningRate; // коэффициент обучения
    bool _gradientClip; // флаг обрезки градиентов для возможной оптимизации

public:
    SGD(INeuralNetworkModel *model,
        double learningRate,
        bool gradientClip);

public:
    // IOprimizer interface
    void updateRule(QMap<QString, Matrix2d<double>> &stepParams) override;
    void step() override;
    //

};

#endif // SGD_H