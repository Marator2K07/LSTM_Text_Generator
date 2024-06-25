#ifndef IOPRIMIZER_H
#define IOPRIMIZER_H

#include <QMap>

#include "matrix2d.h"
#include "ineuralnetworkmodel.h"

///
/// \brief The IOprimizer interface
/// определение функционала оптимизатора модели
/// нейронной сети(обновление параметров сети при обучении)
class IOprimizer
{
public:   
    ///
    /// \brief update обновление параметров модели путем
    /// применения обрезки градиентов и дополнительных
    /// возможностей, зависящих от реализации наследника
    virtual void update() = 0;
};

#endif // IOPRIMIZER_H
