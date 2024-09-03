#include "neuralnetworktextgenerator.h"
#include "matrix2d.cpp"
#include "matrix3d.cpp"

NeuralNetworkTextGenerator::NeuralNetworkTextGenerator(INeuralNetworkModel *neuralNetworkModel,
                                                       QObject *parent)
    : _neuralNetworkModel{neuralNetworkModel}
    , _contextOnAssignment{QList<int>()}
    , QObject{parent}
{
}

NeuralNetworkTextGenerator::NeuralNetworkTextGenerator(QObject *parent)
    : _neuralNetworkModel{nullptr}
    , _contextOnAssignment{QList<int>()}
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

void NeuralNetworkTextGenerator::generate()
{
    // формируем начальные условия на основе контекста
    QList<int> lastCharsIdxs{_contextOnAssignment};
    // генерация начального контекста
    for (int simbolIndex : _contextOnAssignment) {
        QChar symbol = _neuralNetworkModel->embedding()
                           ->charForIndex(simbolIndex);
        emit showGenerationInfo(QString(symbol));
    }
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
        // определяем возможный следующий символ(по его индексу) и пишем его
        int chosenIndex = Distributor::instance()->discrete(lastSoftSymbolPred);
        QChar chosenSymbol = _neuralNetworkModel->embedding()->charForIndex(chosenIndex);
        lastCharsIdxs.push_back(chosenIndex);
        // смотрим, превышен ли размер контекста
        if (lastCharsIdxs.size() > _neuralNetworkModel->embedding()
                                       ->sequenceLength()) {
            lastCharsIdxs.erase(lastCharsIdxs.begin());
        }
        // и наконец посылаем сигнал о готовом сгенерированном символе
        emit showGenerationInfo(QString(chosenSymbol));
        // в случае если символ = символу окончания вывода
        if (chosenSymbol == '.') {
            // даем сигнал завершения процесса и заканчиваем генерацию
            emit generationStoped();
            break;
        }
    }
}

void NeuralNetworkTextGenerator::applyAssignmentForGenerate(QList<int> context)
{
    // в случае превышения контекстом длины последовательности
    while (context.size() > _neuralNetworkModel->embedding()->sequenceLength()) {
        context.pop_front();
    }

    _contextOnAssignment = context;
}
