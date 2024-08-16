#ifndef ITEXTGENERATOR_H
#define ITEXTGENERATOR_H

#include <iostream>
#include <random>

#include "ineuralnetworkmodel.h"
#include "matrix2d.h"

using namespace std;

///
/// \brief The ITextGenerator interface
/// определение функциональности генератора текста
class ITextGenerator
{
public:
    ///
    /// \brief neuralNetworkModel геттер для используемой
    /// во время генерации модели нейронной сети
    /// \return текущая модель нейронной сети
    virtual INeuralNetworkModel *neuralNetworkModel() const = 0;
    ///
    /// \brief setNeuralNetworkModel установка
    /// новой модели используемой нейронной сети
    /// \param model новая модель
    virtual void setNeuralNetworkModel(INeuralNetworkModel *model) = 0;
    ///
    /// \brief generate генерация(предсказание) символов
    /// на основе контекста по данным задания
    virtual void generate() = 0;
    ///
    /// \brief applyAssignmentForTrain слот применения всех необходимых
    /// параметров для начала корректной генерации текста на основе обученной модели
    /// \param context переданный текст(контекст) для генерации
    virtual void applyAssignmentForGenerate(QList<int> context) = 0;

protected:
    ///
    /// \brief showGenerationInfo дополнительный сигнал для отображения разнообразной
    /// информации для связанного виджета во время генерации текста
    /// \param learningInfo необходимая информация для отображения
    virtual void showGenerationInfo(const QString generationInfo) = 0;
    ///
    /// \brief generationStoped сигнал окончания обучения для связанного виджета
    virtual void generationStoped() = 0;

};

#endif // ITEXTGENERATOR_H
