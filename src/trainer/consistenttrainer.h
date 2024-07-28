#ifndef CONSISTENTTRAINER_H
#define CONSISTENTTRAINER_H

#include <QObject>

#include "trainerexception.h"
#include "itrainer.h"
#include "adagrad.h"
#include "sgd.h"

///
/// \brief The OptimizerType enum
/// перечисление для доступных оптимизиаторов при обучении
enum class OptimizerType {
    SGD = 0,
    ADA_GRAD,
    NONE
};

///
/// \brief The ConsistentTrainer class
/// тренер последовательной тренировки на основе текста
class ConsistentTrainer : public QObject,
                          public ITrainer
{
    Q_OBJECT

private:
    INeuralNetworkModel *_model;
    ITextEmbedding<double> *_embedding; // вынесенный эмбеддинг, используемый моделью
    IOptimizer *_optimizer;
    OptimizerType _currentOptimizerType;
    int _sequenceLenght; // длина контекста(последовательности) эмбеддинга модели
    int _batchSize; // длина партии эмбеддинга модели
    long _currentPos; // позиция в данных для обучения
    double _percentageOfTraining; // приблизительная степень обученности модели
    double _epochsCompleted; // количество пройденных эпох обучения с высокой точностью
    double _maxCalculatedLoss; // нужно для вычисления обученности модели

public:
    ConsistentTrainer(INeuralNetworkModel *model, IOptimizer *optimizer);
    ConsistentTrainer(const QString path, INeuralNetworkModel *model);

    // суффикс именования файла с данными о тренировке модели
    static QString TRAINER_DATA_NAME;

    bool operator==(const ConsistentTrainer &trainer);

public:
    // ITrainer interface
    void save(const QString path = QDir::currentPath()) override;
    void load(const QString path = QDir::currentPath()) override;
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
