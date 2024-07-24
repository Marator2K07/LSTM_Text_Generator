#ifndef CONSISTENTTRAINER_H
#define CONSISTENTTRAINER_H

#include <QObject>

#include "trainerexception.h"
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
    ITextEmbedding<double> *_embedding; // вынесенный эмбеддинг, используемый моделью
    IOptimizer *_optimizer;
    int _sequenceLenght; // длина контекста(последовательности) эмбеддинга модели
    int _batchSize; // длина партии эмбеддинга модели
    long _currentPos; // позиция в данных для обучения
    double _percentageOfTraining; // приблизительная степень обученности модели
    double _epochsCompleted; // количество пройденных эпох обучения с высокой точностью

public:
    ConsistentTrainer(INeuralNetworkModel *model, IOptimizer *optimizer);

    // суффикс именования файла с данными о тренировке модели
    static QString TRAINER_DATA_NAME;

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
