#ifndef IOPTIMIZER_H
#define IOPTIMIZER_H

#include <QMap>

#include "matrix2d.h"
#include "ineuralnetworkmodel.h"

///
/// \brief The OptimizerType enum
/// перечисление для доступных оптимизиаторов при обучении
enum class OptimizerType {
    SGD = 0,
    ADA_GRAD,
    NONE
};

///
/// \brief The IOptimizer interface
/// определение функционала оптимизатора модели
/// нейронной сети(обновление параметров сети при обучении)
class IOptimizer
{
public:
    ///
    /// \brief learningRate скорость обучения данного оптимизатора
    /// \return текущая скорость обучения
    virtual double learningRate() const = 0;
    ///
    /// \brief newLearningRate обновление рейтинга
    /// обучения для текущего оптимизатора
    /// \param learningRate рейтинг обучения для обновления
    virtual void newLearningRate(const double learningRate) = 0;
    ///
    /// \brief update обновление параметров модели путем
    /// применения обрезки градиентов и дополнительных
    /// возможностей, зависящих от реализации наследника
    virtual void update() = 0;
};

#endif // IOPTIMIZER_H
