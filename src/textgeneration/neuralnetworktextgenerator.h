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

private:
    INeuralNetworkModel *_neuralNetworkModel;

public:
    explicit NeuralNetworkTextGenerator(INeuralNetworkModel neuralNetworkModel,
                                        QObject *parent = nullptr);

public:
    // ITextGeneration interface
    INeuralNetworkModel *neuralNetworkModel() const override;

public slots:
    // ITextGeneration interface
    void genSymbols(const vector<int> context) override;

signals:
    // ITextGenerator interface
    void symbolReady(QChar) override;

};

#endif // NEURALNETWORKTEXTGENERATOR_H
