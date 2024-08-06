#include "consistenttrainer.h"
#include "matrix2d.cpp"
#include "matrix3d.cpp"

QString ConsistentTrainer::TRAINER_DATA_NAME = "trainerData";
long long ConsistentTrainer::MODEL_POWER_FACTOR = 43403673600;

ConsistentTrainer::ConsistentTrainer(INeuralNetworkModel *model,
                                     IOptimizer *optimizer)
    : _model{model}
    , _embedding{model->embedding()}
    , _optimizer{optimizer}
    , _sequenceLenght{model->embedding()->sequenceLength()}
    , _batchSize{model->embedding()->batchSize()}
    , _currentPos{0}
    , _percentageOfTraining{0.0}
    , _epochsCompleted{0.0}
    , _maxCalculatedLoss{1.0}
    , _iterCountOnAssignment{0}
    , _withSampleOnAssignment{false}
    , _sampleEveryOnAssignment{0}
    , _savePathOnAssignment{QDir::currentPath()}
{
}

ConsistentTrainer::ConsistentTrainer(const QString path,
                                     INeuralNetworkModel *model)
    : _model{model}
    , _embedding{model->embedding()}
    , _optimizer{nullptr}
    , _sequenceLenght{model->embedding()->sequenceLength()}
    , _batchSize{model->embedding()->batchSize()}
    , _iterCountOnAssignment{0}
    , _withSampleOnAssignment{false}
    , _sampleEveryOnAssignment{0}
    , _savePathOnAssignment{QDir::currentPath()}
{
    // оставшиеся три поля класса и оптимизатор подгружаем из файла
    load(path);    
}

bool ConsistentTrainer::operator==(const ConsistentTrainer &trainer)
{
    if (_currentPos != trainer._currentPos) {
        return false;
    }
    if (abs(_percentageOfTraining - trainer._percentageOfTraining) > 1e-3) {
        return false;
    }
    if (abs(_epochsCompleted - trainer._epochsCompleted) > 1e-5) {
        return false;
    }
    if (abs(_maxCalculatedLoss - trainer._maxCalculatedLoss) > 1e-2) {
        return false;
    }
    if (optimizer()->type() != trainer.optimizer()->type() ||
        _optimizer->learningRate() != trainer._optimizer->learningRate()) {
        return false;
    }

    return true;
}

IOptimizer *ConsistentTrainer::optimizer() const
{
    return _optimizer;
}

void ConsistentTrainer::save(const QString path)
{
    // пытаемся открыть файл для сохранения данных о текущем обучении
    QString fileNameTrainer = QString("%1/%2_%3.txt").
                              arg(path, _model->name(), TRAINER_DATA_NAME);
    ofstream fileTrainer;
    fileTrainer.open(fileNameTrainer.toStdString());
    if (!fileTrainer.is_open()) {
        throw TrainerException(
            QString("Catch saving training data exception:\n[%1]\n")
                .arg("Failed to open file")
            );
    }
    // пишем главную информацию об обучении
    fileTrainer << _currentPos << " "
                << _percentageOfTraining << " "
                << _epochsCompleted << " "
                << _maxCalculatedLoss << " "
                << (int)optimizer()->type() << " "
                << _optimizer->learningRate();
    // закрываем файл
    fileTrainer.close();
}

void ConsistentTrainer::load(const QString path)
{
    // пытаемся открыть файл с тренировочными данными
    QString trainerDataFile = QString("%1/%2_%3.txt").
                              arg(path, _model->name(), TRAINER_DATA_NAME);
    ifstream fileTrainerStream;
    fileTrainerStream.open(trainerDataFile.toStdString());
    if (!fileTrainerStream.is_open()) {
        throw TrainerException(
            QString("Catch loading training data exception:\n[%1]\n")
                .arg("Failed to open file")
            );
    }
    // подготовка
    string line;
    double learningRate;
    int intCurrentOptimizerType;
    // считываем данные
    getline(fileTrainerStream, line);
    istringstream rowStreamMain(line);
    rowStreamMain >> _currentPos
        >> _percentageOfTraining
        >> _epochsCompleted
        >> _maxCalculatedLoss
        >> intCurrentOptimizerType
        >> learningRate;
    // подготовка
    OptimizerType optimizerType = (OptimizerType)intCurrentOptimizerType;
    if (_optimizer != nullptr) {
        delete _optimizer;
    }
    // на основе части считанных данных создаем оптимизатор
    switch (optimizerType) {
    case OptimizerType::SGD:
        _optimizer = new SGD(_model, learningRate);
        break;
    case OptimizerType::ADA_GRAD:
        _optimizer = new AdaGrad(_model, learningRate);
        break;
    default:
        break;
    }
    // закрываем файл
    fileTrainerStream.close();
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
                              bool withSample,
                              int sampleEvery,
                              QString savePath)
{
    // подготовка
    int numIter = 0;
    double meanLoss = 0;

    //int currentPos = 36127;
    // последнее для 128_24_50_Layer1 10752
    // последнее для 160_24_48(один слой)(TheRedRoom) 17112
    // //////////////////////////////////////////////// int currentPos = 5608;

    // обучаем:
    while (numIter < iterCount) {
        // если "конец эпохи"
        if (_currentPos + _sequenceLenght + _batchSize + 1 >
            _embedding->text().length()) {
            // после "конца эпохи" сохраняем обученные данные модели
            _model->save(savePath, false);
            // и тренера
            this->save(savePath);
            // даем знать об окончании эпохи обучения
            emit showLearningInfo(QString("end of an era"));
            _currentPos = numIter;
        }
        // генерируем входные и целевые индексы, соотвественно
        Matrix2d<double> inputIndices = _embedding->genTextIndices(_currentPos);
        Matrix2d<double> targetIndices = _embedding->genTextIndices(_currentPos+1);
        // генерируем входные и целевые партии данных, соотвественно
        Matrix3d<double> inputBatch = _embedding->genTextBatch(inputIndices);
        Matrix3d<double> targetBatch = _embedding->genTextBatch(targetIndices);
        // вычислеям потери сети и сравниваем с максимальным значением потери
        double loss = _model->singleStep(inputBatch, targetBatch);        
        if (loss > _maxCalculatedLoss) {
            _maxCalculatedLoss = loss;
        }
        // статистика и средние потери
        QString stepInfo = QString("%1) mean loss - %2; pos - %3")
                               .arg(numIter).arg(loss).arg(_currentPos);
        emit showLearningInfo(stepInfo);
        meanLoss += loss;
        // оптимизируем нейронную сеть
        _optimizer->update();
        // сдвигаем позицию в тексте на размер партии
        _currentPos += _batchSize;
        // возможная генерация вывода для анализа
        if (withSample && numIter % sampleEvery == 0) {
            sampleOutput(rand() % _embedding->vocabSize(), '.');
        }
        numIter++;
    }
    // вычисляем главные параметры статистики
    _percentageOfTraining = (_maxCalculatedLoss - meanLoss/ iterCount) / 100;
    double temp = (double)iterCount * (double)_batchSize
                  / (double)_embedding->text().size();
    _epochsCompleted += temp;
    // в конце всегда сохраняем данные нейронной модели
    _model->save(savePath, false);
    // и тренера
    this->save(savePath);
    // и выводим оценивающие данные
    emit showLearningInfo(QString("end of learning"));
    emit showLearningInfo(QString("current position - %1").arg(_currentPos));
    emit showLearningInfo(QString("mean loss value - %1").arg(meanLoss/iterCount));
    emit showLearningInfo(QString("percentage of training - %1")
                              .arg(_percentageOfTraining));
    emit showLearningInfo(QString("epochs completed - %1")
                              .arg(QString::number(_epochsCompleted, 'f', 10)));
    // не забываем обновить статус для связанного виджета
    updateStatus();
}

void ConsistentTrainer::updateStatus()
{
    // даем знать связанным виджетам об изменениях
    emit percentageOfTrainingUpdated(_percentageOfTraining);
    emit epochsCompletedUpdated(_epochsCompleted);
    emit recommendedNumberOfTrainingIter(
        (1 / (double)_model->power()) * MODEL_POWER_FACTOR
        );
}

void ConsistentTrainer::refreshOptimizerStatus(IOptimizer *optimizer)
{
    // если оптимизатор был проинициализирован
    if (_optimizer != nullptr) {
        delete _optimizer;
    }
    _optimizer = optimizer;
}
