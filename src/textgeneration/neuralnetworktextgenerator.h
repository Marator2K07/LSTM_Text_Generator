#ifndef NEURALNETWORKTEXTGENERATOR_H
#define NEURALNETWORKTEXTGENERATOR_H

#include <QObject>

#include "itextgeneration.h"

///
/// \brief The NeuralNetworkTextGenerator class
/// генератор текста на основе модели нейронной сети
class NeuralNetworkTextGenerator : public QObject,
                                   public ITextGeneration
{
    Q_OBJECT

public:
    explicit NeuralNetworkTextGenerator(QObject *parent = nullptr);

public:
    // ITextGeneration interface
    QChar genSymbol(const Matrix2d<double> context) override;

};

#endif // NEURALNETWORKTEXTGENERATOR_H
