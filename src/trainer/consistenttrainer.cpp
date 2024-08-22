#include "consistenttrainer.h"
#include "matrix2d.cpp"
#include "matrix3d.cpp"

QString ConsistentTrainer::TRAINER_DATA_NAME = "trainerData";
long long ConsistentTrainer::MODEL_POWER_FACTOR = 130211020800;

void ConsistentTrainer::showFinalData()
{
    emit showLearningInfo(QString("end of learning\n"));
    emit showLearningInfo(QString("current position - %1\n").arg(_currentPos));
    emit showLearningInfo(QString("mean loss value - %1\n")
                              .arg(_totalLosses/_iterCountOnAssignment));
    emit showLearningInfo(QString("percentage of training - %1\n")
                              .arg(_percentageOfTraining));
    emit showLearningInfo(QString("epochs completed - %1\n")
                              .arg(QString::number(_epochsCompleted, 'f', 10)));
    // не забываем обновить статус для связанного виджета
    updateStatus();
}

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
    , _totalLosses{0.0}
    , _trainStoped{false}
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
    , _totalLosses{0.0}
    , _trainStoped{false}
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
    fileTrainer << _currentPos << " " << _percentageOfTraining << " "
                << _epochsCompleted << " " << _maxCalculatedLoss << " "
                << (int)optimizer()->type() << " " << _optimizer->learningRate();
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
    rowStreamMain >> _currentPos >> _percentageOfTraining >> _epochsCompleted
        >> _maxCalculatedLoss >> intCurrentOptimizerType >> learningRate;
    // подготовка для оптимизатора
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
    // вывод первого символа и предисловия:
    emit showLearningInfo(QString("sample["));
    emit showLearningInfo(QString(_embedding->charForIndex(startCharIdx)));
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
        // определяем возможный следующий символ(по его индексу) и пишем его
        int chosenIndex = Distributor::instance()->discrete(lastSoftSymbolPred);
        QChar chosenSymbol = _embedding->charForIndex(chosenIndex);
        lastCharsIdxs.push_back(chosenIndex);
        // смотрим, превышен ли размер контекста
        if (lastCharsIdxs.size() > _sequenceLenght) {
            lastCharsIdxs.erase(lastCharsIdxs.begin());
        }
        // и наконец выводим найденный символ
        emit showLearningInfo(QString(chosenSymbol));
        // в случае если символ = символу окончания вывода
        if (chosenSymbol == endingChar) {
            break;
        }
    }
    emit showLearningInfo(QString("]\n"));
}

void ConsistentTrainer::train()
{
    // подготовка
    int numIter = 0;
    _totalLosses = 0;
    _trainStoped = false;
    // обучаем:
    while (numIter < _iterCountOnAssignment) {
        // если "конец эпохи"
        if (_currentPos + _sequenceLenght + _batchSize + 1 >
            _embedding->text().length()) {
            // после "конца эпохи" сохраняем обученные данные модели
            _model->save(_savePathOnAssignment, false);
            // и тренера
            this->save(_savePathOnAssignment);
            // даем знать об окончании эпохи обучения
            emit showLearningInfo(QString("end of an era\n"));
            _currentPos = 0; // ради более стабильного обучения
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
        QString stepInfo = QString("%1) mean loss - %2; pos - %3\n")
                               .arg(numIter).arg(loss).arg(_currentPos);
        emit showLearningInfo(stepInfo);
        emit trainingProgress(
            (double)(numIter+1) / (double)_iterCountOnAssignment * 100
            );
        _totalLosses += loss;
        // оптимизируем нейронную сеть
        _optimizer->update();
        // сдвигаем позицию в тексте на размер партии
        _currentPos += _batchSize;
        // возможная генерация вывода для анализа
        if (_withSampleOnAssignment && numIter % _sampleEveryOnAssignment == 0) {
            sampleOutput(rand() % _embedding->vocabSize(), '.');
        }        
        numIter++;
        // в случае преждевременной остановки обучения
        if (_trainStoped) {
            emit showLearningInfo(QString("premature training stop\n"));
            emit trainingProgress(100);
            break;
        }
    }
    // вычисляем главные параметры статистики
    _percentageOfTraining
        = ((_maxCalculatedLoss - _totalLosses / _iterCountOnAssignment)
            / _maxCalculatedLoss) * 100;
    double temp = (double)_iterCountOnAssignment * (double)_batchSize
                  / (double)_embedding->text().size();
    _epochsCompleted += temp;
    // в конце всегда сохраняем данные нейронной модели
    _model->save(_savePathOnAssignment, false);
    // и тренера
    this->save(_savePathOnAssignment);
    // и выводим заключительную информацию об обучении
    showFinalData();
    // даем сигнал завершения процесса
    emit trainingStoped();
}

void ConsistentTrainer::stop()
{
    _trainStoped = true;
}

void ConsistentTrainer::applyAssignmentForTrain(int iterCount,
                                                bool withSample,
                                                int sampleEvery,
                                                QString savePath)
{
    _iterCountOnAssignment = iterCount;
    _withSampleOnAssignment = withSample;
    _sampleEveryOnAssignment = sampleEvery;
    _savePathOnAssignment = savePath;
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
