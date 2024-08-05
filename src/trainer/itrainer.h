#ifndef ITRAINER_H
#define ITRAINER_H

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
    /// \param startCharIdx индекс символа для старта генерации
    /// \param endingChar конечный символ
    virtual void sampleOutput(int startCharIdx, char endingChar = '.') = 0;
    ///
    /// \brief train тренирует модель генерации текста
    /// \param iterCount количество шагов обучения
    /// \param textSample флаг наличия вывода сгенерированного
    /// текста, используя последнюю версию модели
    /// \param sampleEvery частота вывода текста
    virtual void train(int iterCount,
                       bool textSample = false,
                       int sampleEvery = 100) = 0;
    ///
    /// \brief updateStatus метод, для объединения
    /// посыла всех необходимых сигналов, связанных с соотвествующим
    /// виджетом для показа статистики информации
    virtual void updateStatus() = 0;

protected:
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
    /// \brief sampleSymbolReady сигнал для связанного виджета о готовности
    /// нового предсказанного символа на текущей стадии обученности модели
    /// \param newSymbol новый символ для отображения
    virtual void sampleSymbolReady(QChar newSymbol) = 0;
    ///
    /// \brief showLearningInfo дополнительный сигнал для отображения разнообразной
    /// информации для связанного виджета во время обучения модели
    /// \param learningInfo необходимая информация для отображения
    virtual void showLearningInfo(QString learningInfo) = 0;
};

#endif // ITRAINER_H
