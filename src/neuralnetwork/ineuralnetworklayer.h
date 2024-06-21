#ifndef INEURALNETWORKLAYER_H
#define INEURALNETWORKLAYER_H

#include <QMap>
#include <QString>

#include "matrix3d.h"
#include "activationfunctions.h"

///
/// \brief The INeuralNetworkLayer interface
/// описание функциональности слоя нейронной сети
class INeuralNetworkLayer
{
public:
    ///
    /// \brief initParams инциализация параметров слоя
    /// по размерам входящей трехмерной матрицы
    /// \param initMatrix матрица для инициализации
    virtual void initParams(Matrix3d<double> initMatrix) = 0;
};

#endif // INEURALNETWORKLAYER_H
