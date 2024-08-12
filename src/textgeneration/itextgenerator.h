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
    /// \brief generate генерация(предсказание) символов на основе контекста
    /// \param context контекст текста (индексы символов в строке)
    virtual void generate(const vector<int> context) = 0;

protected:
    ///
    /// \brief showGenerationInfo дополнительный сигнал для отображения разнообразной
    /// информации для связанного виджета во время генерации текста
    /// \param learningInfo необходимая информация для отображения
    virtual void showGenerationInfo(const QString generationInfo) = 0;

};

#endif // ITEXTGENERATOR_H
