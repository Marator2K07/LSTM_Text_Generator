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
    // формируем начальные условия для последовательности
    vector<int> lastCharsIdxs;
    lastCharsIdxs.push_back(startCharIdx);
    // подготовка для будущей рандомизации
    random_device rd;
    mt19937 gen(rd());
    // вывод:
    cout << _embedding->idxToChar().value(startCharIdx);
    while (true) {
        // начальная входная партия состоящая
        // из lastCharsIdxs.size() символов
        Matrix3d<double> inputCharBatch
            = Matrix3d<double>::zeroM(1, lastCharsIdxs.size(),
                                      _embedding->vocabSize());
        // заполняем начальную партию индексов
        for (int seqI = 0; seqI < lastCharsIdxs.size(); ++seqI) {
            inputCharBatch.setValue(0, seqI, lastCharsIdxs[seqI], 1.0);
        }
        // партия предсказания после прохода по нейронной сети
        Matrix3d<double> predictionBatch = _model->forward(inputCharBatch);
        // приведение предсказания к корректному виду
        Matrix3d<double> softmaxPredBatch = Matrix3d<double>(
            ActivationFunctions<double>::softmax(&predictionBatch)
            );
        vector<double> lastSoftSymbolPred(
            softmaxPredBatch.dataToVector()
                .at(0).dataToVector()
                .at(lastCharsIdxs.size()-1)
            );
        // определяем возможный следующий символ
        discrete_distribution<> dist(lastSoftSymbolPred.begin(),
                                     lastSoftSymbolPred.end());
        // находим предсказанный индекс и его символ, пишем его в последовательность
        int chosenIndex = dist(gen);
        char chosenSymbol = _embedding->idxToChar().value(chosenIndex);
        lastCharsIdxs.push_back(chosenIndex);
        // смотрим, превышен ли размер контекста
        if (lastCharsIdxs.size() > _sequenceLenght) {
            lastCharsIdxs.erase(lastCharsIdxs.begin());
        }
        // и наконец выводим найденный символ
        cout << chosenSymbol;
        // в случае если символ = символу окончания вывода
        if (chosenSymbol == endingChar) {
            break;
        }

        // cout << endl << "[" ;        for (const int value : lastCharsIdxs) {
        //     cout << value << "|";
        // }
        // cout << "]" << endl;
    }
    cout << endl;
}

void ConsistentTrainer::train(int iterCount,
                              bool textSample,
                              int sampleEvery)
{
    int numIter = 0;
    double meanLoss = 0;
    //int currentPos = 36127;
    // последнее для 128_24_50_Layer1 10752
    // последнее для 160_24_48(один слой)(TheRedRoom) 17112
    int currentPos = 30558;
    // обучаем:
    while (numIter < iterCount) {
        // "конец эпохи"
        if (currentPos + _sequenceLenght + _batchSize + 1 >
            _embedding->text().length()) {
            // после "конца эпохи" сохраняем обученные данные
            // и завершаем текущий этап обучения
            foreach (INeuralNetworkLayer *layer, _model->layers()) {
                layer->saveParams(QDir::currentPath());
            }
            cout << "end of an era" << endl;
            currentPos = numIter;
        }
        // генерируем входные и целевые индексы, соотвественно
        Matrix2d<double> inputIndices = _embedding->genTextIndices(currentPos);
        Matrix2d<double> targetIndices = _embedding->genTextIndices(currentPos+1);
        // генерируем входные и целевые партии данных, соотвественно
        Matrix3d<double> inputBatch = _embedding->genTextBatch(inputIndices);
        Matrix3d<double> targetBatch = _embedding->genTextBatch(targetIndices);
        // вычислеям потери сети
        double loss = _model->singleStep(inputBatch, targetBatch);
        cout << numIter << ") " << loss << " pos - " << currentPos << endl;
        meanLoss += loss;
        // оптимизируем нейронную сеть
        _optimizer->update();
        // сдвигаем позицию в тексте на размер партии
        currentPos += _batchSize;
        // возможная генерация вывода для анализа
        if (textSample && numIter % sampleEvery == 0) {
            sampleOutput(rand() % _embedding->vocabSize(), '.');
        }
        numIter++;
    }

    foreach (INeuralNetworkLayer *layer, _model->layers()) {
        layer->saveParams(QDir::currentPath());
    }
    cout << "end of iter" << " currentPos - " << currentPos << endl;
    cout << "mean loss value - " << meanLoss / iterCount << endl;
}
