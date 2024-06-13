#ifndef INEURALNETWORKNODE_H
#define INEURALNETWORKNODE_H

#include <QMap>
#include <QString>

#include "matrix2d.h"

///
/// \brief The INeuralNetworkNode interface
/// описание функциональности узла нейронной сети
class INeuralNetworkNode
{
public:
    ///
    /// \brief forward прямой проход - вычисление прогнозируемых значений
    /// \param in словарь входов для данных и скрытых состояний
    /// \param params заданные параметры слоя для данного узла
    /// \return словарь выходных данных и скрытых состояний
    QMap<QString, Matrix2d<double>>
    forward(QMap<QString, Matrix2d<double>> in,
            QMap<QString, QMap<QString, Matrix2d<double>>> &params);
    ///
    /// \brief backward обратное распостранение градиента по узлу слоя
    /// \param outGrad словарь градиентов по выходу и скрытым состояниям
    /// \param params заданные параметры слоя для данного узла
    /// \return словарь градиентов по входным данным и скрытым состояниям
    QMap<QString, Matrix2d<double>>
    backward(QMap<QString, Matrix2d<double>> outGrad,
             QMap<QString, QMap<QString, Matrix2d<double>>> &params);
};

#endif // INEURALNETWORKNODE_H
