#include "consistenttrainer.h"

ConsistentTrainer::ConsistentTrainer(INeuralNetworkModel *model,
                                     ITextEmbedding<double> *embedding,
                                     IOptimizer *optimizer,
                                     int sequenceLenght,
                                     int batchSize)
    : _model{model}
    , _embedding{embedding}
    , _optimizer{optimizer}
    , _sequenceLenght{sequenceLenght}
    , _batchSize{batchSize}
{
}

void ConsistentTrainer::sampleOutput(int startCharIdx, int sampleLenght)
{

}

void ConsistentTrainer::train(int iterCount, bool textSample, int sampleEvery)
{

}
