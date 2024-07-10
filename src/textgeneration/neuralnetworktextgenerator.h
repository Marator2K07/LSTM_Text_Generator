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
    void genSymbols(const vector<int> context) override;

signals:
    // ITextGenerator interface
    void symbolReady(QChar) override;

};

#endif // NEURALNETWORKTEXTGENERATOR_H
