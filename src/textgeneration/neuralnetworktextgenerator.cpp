#include "neuralnetworktextgenerator.h"
#include "matrix2d.cpp"
#include "matrix3d.cpp"

NeuralNetworkTextGenerator::NeuralNetworkTextGenerator(INeuralNetworkModel neuralNetworkModel,
                                                       QObject *parent)
    : _neuralNetworkModel{neuralNetworkModel}
    , QObject{parent}
{
}

INeuralNetworkModel *NeuralNetworkTextGenerator::neuralNetworkModel() const
{
    return _neuralNetworkModel;
}

void NeuralNetworkTextGenerator::setNeuralNetworkModel(INeuralNetworkModel *model)
{
    _neuralNetworkModel = model;
}

void NeuralNetworkTextGenerator::genSymbols(const vector<int> context)
{
    // формируем начальные условия на основе контекста
    vector<int> lastCharsIdxs{context};
    // подготовка для будущей рандомизации
    random_device rd;
    mt19937 gen(rd());
    // генерация символов:
    while(true) {
        // начальная входная партия состоящая
        // из lastCharsIdxs.size() символов
        Matrix3d<double> inputCharBatch
            = Matrix3d<double>::zeroM(
                1,
                lastCharsIdxs.size(),
                _neuralNetworkModel->embedding()->vocabSize()
                );
        // заполняем начальную партию индексов
        for (int seqI = 0; seqI < lastCharsIdxs.size(); ++seqI) {
            inputCharBatch.setValue(0, seqI, lastCharsIdxs[seqI], 1.0);
        }
        // партия предсказания после прохода по нейронной сети
        Matrix3d<double> predictionBatch
            = _neuralNetworkModel->forward(inputCharBatch);
        // приведение предсказания к корректному виду
        Matrix3d<double> softmaxPredBatch = Matrix3d<double>(
            ActivationFunctions<double>::softmax(&predictionBatch)
            );
        // получаем вектор с предсказаниями следующего символа
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
        char chosenSymbol = _neuralNetworkModel->embedding()
                                ->idxToChar().value(chosenIndex);
        lastCharsIdxs.push_back(chosenIndex);
        // смотрим, превышен ли размер контекста
        if (lastCharsIdxs.size() > _neuralNetworkModel->embedding()
                                       ->sequenceLength()) {
            lastCharsIdxs.erase(lastCharsIdxs.begin());
        }
        // и наконец посылаем сигнал о готовом сгенерированном символе
        emit symbolReady(QChar(chosenIndex));
        // в случае если символ = символу окончания вывода
        if (chosenSymbol == '.') {
            break;
        }
    }
}
