#ifndef CONSISTENTTRAINER_H
#define CONSISTENTTRAINER_H

#include "itrainer.h"

class ConsistentTrainer : public ITrainer
{
public:
    ConsistentTrainer();

public:
    // ITrainer interface
    void sampleOutput(int startCharIdx, int sampleLenght) override;
    void train(int iterCount, bool textSample, int sampleEvery) override;
    //

};

#endif // CONSISTENTTRAINER_H
