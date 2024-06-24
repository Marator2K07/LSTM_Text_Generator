#ifndef INEURALNETWORKLAYER_H
#define INEURALNETWORKLAYER_H

#include <QList>

#include "matrix3d.h"
#include "lstmnode.h"
#include "activationfunctions.h"
#include "neuralnetworkexception.h"

///
/// \brief The INeuralNetworkLayer interface
/// описание функциональности слоя нейронной сети
class INeuralNetworkLayer
{
public:
    ///
    /// \brief initParams инициализация параметров слоя
    /// по размерам входящей трехмерной матрицы
    /// \param initMatrix матрица для инициализации
    virtual void initParams(const Matrix3d<double> initMatrix) = 0;
    ///
    /// \brief clearGraients чистка накопившихся градиентов слоя
    virtual void clearGradients() = 0;
    ///
    /// \brief forward вычисление предсказания на основе
    /// текущего состояния нейронов
    /// \param xSequenceIn трехмерная матрица партии входящих значений
    /// \return обработанная слоем партия значений
    virtual Matrix3d<double> forward(Matrix3d<double> xSequenceIn) = 0;
    ///
    /// \brief backward обратное распостранение ошибки - корректировка
    /// коэффициентов слоя/модели в направлении уменьшения ошибки предсказания
    /// \param xSequenceOutGrad трехмерная матрица партии градиентов по выходу
    /// \return партия градиентов по входу
    virtual Matrix3d<double> backward(Matrix3d<double> xSequenceOutGrad) = 0;
};

#endif // INEURALNETWORKLAYER_H
