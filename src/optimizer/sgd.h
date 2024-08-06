#ifndef SGD_H
#define SGD_H

#include "ioptimizer.h"

///
/// \brief The SGD class
/// оптимизатор нейронной сети Stochastic Gradient Descent
/// (стохастический градиентный спуск)
class SGD : public IOptimizer
{
private:
    INeuralNetworkModel *_model; // модель нейронной сети
    double _learningRate; // коэффициент обучения
    bool _gradientClip; // флаг обрезки градиентов для возможной оптимизации

public:
    SGD(INeuralNetworkModel *model,
        double learningRate = 0.01,
        bool gradientClip = true);

public:
    // IOprimizer interface
    OptimizerType type() const override;
    double learningRate() const override;
    void newLearningRate(const double learningRate) override;
    void update() override;
    //

};

#endif // SGD_H
