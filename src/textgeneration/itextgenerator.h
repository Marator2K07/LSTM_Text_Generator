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
    /// \brief genSymbols предсказание символов на основе контекста
    /// \param context контекст текста (индексы символов в строке)
    virtual void genSymbols(const vector<int> context) = 0;

signals:
    ///
    /// \brief symbolReady сигнал о готовности сгенерированного символа
    /// \param symbol новый сгенерированный символ
    virtual void symbolReady(const QChar symbol) = 0;

};

#endif // ITEXTGENERATOR_H
