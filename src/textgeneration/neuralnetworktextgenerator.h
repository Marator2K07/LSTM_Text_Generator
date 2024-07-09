#ifndef NEURALNETWORKTEXTGENERATOR_H
#define NEURALNETWORKTEXTGENERATOR_H

#include <QObject>

#include "itextgenerator.h"

///
/// \brief The NeuralNetworkTextGenerator class
/// генератор текста на основе модели нейронной сети
class NeuralNetworkTextGenerator : public QObject,
                                   public ITextGenerator
{
    Q_OBJECT

public:
    explicit NeuralNetworkTextGenerator(QObject *parent = nullptr);

public:
    // ITextGeneration interface
    QChar genSymbol(const vector<int> context) override;

};

#endif // NEURALNETWORKTEXTGENERATOR_H
