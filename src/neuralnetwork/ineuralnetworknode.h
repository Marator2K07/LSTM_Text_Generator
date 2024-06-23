#ifndef INEURALNETWORKNODE_H
#define INEURALNETWORKNODE_H

#include <QMap>
#include <QString>

#include "matrix2d.h"
#include "activationfunctions.h"

///
/// \brief The INeuralNetworkNode interface
/// описание функциональности узла нейронной сети
class INeuralNetworkNode
{
public:
    /// \brief forward прямой проход - вычисление прогнозируемых значений
    /// \param xIn матрица входа данных
    /// \param hIn матрица входа состояния слоя
    /// \param cIn матрица входа состояния ячейки
    /// \param layerParams заданные параметры слоя для данного узла
    /// \return словарь выходных данных и скрытых состояний
    virtual QMap<QString, Matrix2d<double>>
    forward(Matrix2d<double> xIn,
            Matrix2d<double> hIn,
            Matrix2d<double> cIn,
            QMap<QString, QMap<QString, Matrix2d<double>>> &layerParams) = 0;
    ///
    /// \brief backward обратное распостранение градиента по узлу слоя
    /// \param xOutGrad матрица градиентов по выходу для значений
    /// \param hOutGrad матрица градиентов по выходу для состояния слоя
    /// \param cOutGrad матрица градиентов по выходу для состояния ячейки
    /// \param layerParams заданные параметры слоя для данного узла
    /// \return словарь градиентов по входным данным и входным скрытым состояниям
    virtual QMap<QString, Matrix2d<double>>
    backward(Matrix2d<double> xOutGrad,
             Matrix2d<double> hOutGrad,
             Matrix2d<double> cOutGrad,
             QMap<QString, QMap<QString, Matrix2d<double>>> &layerParams) = 0;
};

#endif // INEURALNETWORKNODE_H
