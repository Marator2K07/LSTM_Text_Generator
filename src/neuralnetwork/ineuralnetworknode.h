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
    /// \param input словарь входов для данных и скрытых состояний
    /// \param layerParams заданные параметры слоя для данного узла
    /// \return словарь выходных данных и скрытых состояний
    virtual QMap<QString, Matrix2d<double>>
    forward(QMap<QString, Matrix2d<double>> input,
            QMap<QString, QMap<QString, Matrix2d<double>>> &layerParams) = 0;
    ///
    /// \brief backward обратное распостранение градиента по узлу слоя
    /// \param outputGrad словарь градиентов по выходу и скрытым состояниям
    /// \param layerParams заданные параметры слоя для данного узла
    /// \return словарь градиентов по входным данным и скрытым состояниям
    virtual QMap<QString, Matrix2d<double>>
    backward(QMap<QString, Matrix2d<double>> outputGrad,
             QMap<QString, QMap<QString, Matrix2d<double>>> &layerParams) = 0;
};

#endif // INEURALNETWORKNODE_H
