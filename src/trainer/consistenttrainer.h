#ifndef CONSISTENTTRAINER_H
#define CONSISTENTTRAINER_H

#include <QObject>

#include "itrainer.h"

///
/// \brief The ConsistentTrainer class
/// тренер последовательной тренировки на основе текста
class ConsistentTrainer : public QObject,
                          public ITrainer
{
    Q_OBJECT

private:
    INeuralNetworkModel *_model;
    ITextEmbedding<double> *_embedding;
    IOptimizer *_optimizer;
    int _sequenceLenght;
    int _batchSize;

public:
    ConsistentTrainer(INeuralNetworkModel *model,
                      ITextEmbedding<double> *embedding,
                      IOptimizer *optimizer,
                      int sequenceLenght = 16,
                      int batchSize = 32);

public:
    // ITrainer interface
    void sampleOutput(int startCharIdx, char endingChar = '.') override;
    void train(int iterCount, bool textSample, int sampleEvery) override;
    //

signals:
    // ITrainer interface
    void percentageOfTrainingUpdated(double newPercentageOfTraining) override;
    void epochsCompletedUpdated(double newEpochsCompleted) override;
    //

};

#endif // CONSISTENTTRAINER_H
