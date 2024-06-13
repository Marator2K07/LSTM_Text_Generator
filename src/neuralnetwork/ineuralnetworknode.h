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
};

#endif // INEURALNETWORKNODE_H
