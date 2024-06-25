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
    /// \brief updateRule обновление модели на основе переданных параметров
    /// \param stepParams переданные параметры
    virtual void updateRule(QMap<QString, Matrix2d<double>> &stepParams) = 0;
    ///
    /// \brief step обновление параметров модели путем
    /// применения правила обновления и дополнительных возможностей
    virtual void step() = 0;
};

#endif // IOPRIMIZER_H
