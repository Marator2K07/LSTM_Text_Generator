#ifndef ADAGRAD_H
#define ADAGRAD_H

#include "ioptimizer.h"

///
/// \brief The AdaGrad class
/// оптимизатор нейронной сети Adaptive Gradient
/// (Адаптивный градиент)
class AdaGrad : public IOptimizer
{
private:
    INeuralNetworkModel *_model; // модель нейронной сети
    double _learningRate; // коэффициент обучения
    double _epsilon; // вспомогательная переменная для исключения / на ноль
    bool _gradientClip; // флаг обрезки градиентов для возможной оптимизации
    bool _first; // флаг первой инициализации параметров
    QList<QMap<QString, Matrix2d<double>>> _sumSquares; // суммы квадратов град.

public:
    AdaGrad(INeuralNetworkModel *model,
            double learningRate = 0.01,
            double epsilon = 1e-7,
            bool gradientClip = true);

public:
    // IOptimizer interface
    void update() override;
    //

};

#endif // ADAGRAD_H
