#ifndef LSTMLAYER_H
#define LSTMLAYER_H

#include "ineuralnetworklayer.h"

///
/// \brief The LSTMLayer class
/// слоя нейронной сети типа LSTM
class LSTMLayer : public INeuralNetworkLayer
{
private:
    QString _name; // имя слоя для сохранения и загрузок параметров
    int _hiddenSize;
    int _outputSize;
    int _vocabSize;
    double _weightScale; // точность весов
    Matrix2d<double> _startH; // стартовое состояние слоя
    Matrix2d<double> _startC; // стартовое состояние ячейки/узла
    bool _firstStep; // флаг начальной реализации    
    QList<LSTMNode> _cells; // ячейки с нейронными узлами
    QMap<QString, QMap<QString, Matrix2d<double>>> _params;

public:
    LSTMLayer(QString name,
              int hiddenSize,
              int outputSize,
              double weightScale = 0.01);

    bool operator==(LSTMLayer layer);

public:
    // INeuralNetworkLayer interface
    void updateParam(const QString firstKey,
                     const QString secondKey,
                     const Matrix2d<double> value) override;
    void saveParams(QString path) override;
    void loadParams(QString path) override;
    void initParams(const Matrix3d<double> initMatrix) override;
    QMap<QString, QMap<QString, Matrix2d<double>>> params() const override;
    void clearGradients() override;
    Matrix3d<double> forward(Matrix3d<double> xSequenceIn) override;
    Matrix3d<double> backward(Matrix3d<double> xSequenceOutGrad) override;
    //

};

#endif // LSTMLAYER_H
