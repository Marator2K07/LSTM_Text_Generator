#ifndef ITRAINER_H
#define ITRAINER_H

#include <QRandomGenerator>

#include "ineuralnetworkmodel.h"
#include "itextembedding.h"
#include "ioptimizer.h"

///
/// \brief The ITrainer interface
/// определение функционала тренера модели
class ITrainer
{
public:
    ///
    /// \brief optimizer обычный геттер для оптимизатора
    /// \return используемый тренером оптимизатор
    virtual IOptimizer *optimizer() const = 0;
    ///
    /// \brief save cохранение всех необходимых
    /// параметров тренера нейронной сети в отдельной папке
    /// \param path путь сохранения
    virtual void save(const QString path = QDir::currentPath()) = 0;
    ///
    /// \brief load загрузка всех необходимых параметров из папки с моделью
    /// \param path путь к папке с моделью
    virtual void load(const QString path = QDir::currentPath()) = 0;
    ///
    /// \brief sampleOutput вывод текста на основе
    /// текущей модели и ее степени обученности до
    /// первого символа окончания, по умолчанию точки
    /// \param endingChar конечный символ
    virtual void sampleOutput(const QChar endingChar) = 0;
    ///
    /// \brief train слот тренировки модели генерации текста по данным задания
    virtual void train() = 0;
    ///
    /// \brief applyAssignmentForTrain слот применения всех необходимых
    /// параметров для начала корректного обучения модели в отдельном потоке
    /// \param iterCount необходимое количество шагов обучения
    /// \param withSample флаг наличия генерации
    /// примера, используя последнюю версию модели
    /// \param sampleEvery частота вывода текста примера
    /// \param savePath путь сохранения данных модели
    /// и тренера после завершения обучения(или во время обучения)
    virtual void applyAssignmentForTrain(int iterCount,
                                         bool withSample = false,
                                         int sampleEvery = 100,
                                         QString savePath = QDir::currentPath()) = 0;
    ///
    /// \brief stop преждевременная остановка тренировки модели
    virtual void stop() = 0;
    ///
    /// \brief updateStatus метод, для объединения
    /// посыла всех необходимых сигналов, связанных с соотвествующим
    /// виджетом для показа статистики информации
    virtual void updateStatus() = 0;
    ///
    /// \brief refreshOptimizerStatus обновление статуса текущего оптимизатора
    /// \param optimizer оптимизатор для сверки и обновления статуса
    virtual void refreshOptimizerStatus(IOptimizer *optimizer) = 0;

protected:
    ///
    /// \brief modelIsCorrect сигнал, оповещающий, что модель нейронной сети
    /// корректна, она успешно загружена и ее можно обучать
    virtual void modelIsCorrect() = 0;
    ///
    /// \brief modelIsBroken в случае некорректного обучения модели
    /// и появления испорченных параметров нужно послать сигнал-уведомление
    /// и прекратить обучение или вовсе не загружать модель
    virtual void modelIsBroken() = 0;
    ///
    /// \brief percentageOfTrainingUpdated сигнал обновления процента обученности
    /// \param newPercentageOfTraining новый текущий процент обученности модели
    virtual void percentageOfTrainingUpdated(double newPercentageOfTraining) = 0;
    ///
    /// \brief epochsCompletedUpdated сигнал обновления количества пройденных эпох
    /// \param newEpochsCompleted новое количество пройденных эпох обучения
    virtual void epochsCompletedUpdated(double newEpochsCompleted) = 0;
    ///
    /// \brief recommendedNumberOfTrainingIter сигнал для получения рекомендованного
    /// (относительно максимального) количества итерация для обучения текущей модели
    /// \param iterCount рекомендованное количество итераций
    virtual void recommendedNumberOfTrainingIter(int iterCount) = 0;
    ///
    /// \brief showLearningInfo дополнительный сигнал для отображения разнообразной
    /// информации для связанного виджета во время обучения модели
    /// \param learningInfo необходимая информация для отображения
    virtual void showLearningInfo(const QString learningInfo) = 0;
    ///
    /// \brief trainingProgress уведомление о прогрессе данного
    /// задания по обучению выбранной модели
    /// \param percentCompleted сколько процентов задания выполнено
    virtual void trainingProgress(int percentCompleted) = 0;
    ///
    /// \brief learningStoped сигнал окончания обучения для связанного виджета
    virtual void trainingStoped() = 0;
};

#endif // ITRAINER_H
