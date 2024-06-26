#ifndef IOPTIMIZER_H
#define IOPTIMIZER_H

#include <QMap>

#include "matrix2d.h"
#include "ineuralnetworkmodel.h"

///
/// \brief The IOptimizer interface
/// определение функционала оптимизатора модели
/// нейронной сети(обновление параметров сети при обучении)
class IOptimizer
{
public:   
    ///
    /// \brief update обновление параметров модели путем
    /// применения обрезки градиентов и дополнительных
    /// возможностей, зависящих от реализации наследника
    virtual void update() = 0;
};

#endif // IOPTIMIZER_H
