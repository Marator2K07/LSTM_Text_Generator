#include "consistenttrainer.h"
#include "matrix2d.cpp"
#include "matrix3d.cpp"

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

void ConsistentTrainer::sampleOutput(int startCharIdx, char endingChar)
{
    // подготовка для будущей рандомизации
    random_device rd;
    mt19937 gen(rd());
    // вывод:
    cout << _embedding->idxToChar().value(startCharIdx);
    while (true) {
        // начальная входная партия состоящая из одного символа
        Matrix3d<double> inputCharBatch
            = Matrix3d<double>::zeroM(1, 1 ,_embedding->vocabSize());
        inputCharBatch.setValue(0, 0, startCharIdx, 1.0);
        // партия предсказания после прохода по нейронной сети
        Matrix3d<double> predictionBatch = _model->forward(inputCharBatch);
        // приведение предсказания к корректному виду
        Matrix3d<double> softmaxPredBatch = Matrix3d<double>(
            ActivationFunctions<double>::softmax(&predictionBatch)
            );
        // определяем возможный следующий символ и печатаем его
        vector<double> predictLine = softmaxPredBatch.toLine();
        discrete_distribution<> dist(predictLine.begin(),
                                     predictLine.end());
        int chosenIndex = dist(gen);
        char chosenSymbol = _embedding->idxToChar().value(chosenIndex);
        cout << chosenSymbol;
        // в случае если символ = символу окончания вывода
        if (chosenSymbol == endingChar) {
            break;
        }
    }
    cout << endl;
}

void ConsistentTrainer::train(int iterCount, bool textSample, int sampleEvery)
{

}
