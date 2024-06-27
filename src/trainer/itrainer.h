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
    /// \brief sampleOutput вывод текста на основе
    /// текущей модели и ее степени обученности
    /// \param startCharIdx индекс символа для старта генерации
    /// \param sampleLenght длина генерации
    virtual void sampleOutput(int startCharIdx, int sampleLenght) = 0;
    ///
    /// \brief train тренирует модель генерации текста
    /// \param iterCount количество шагов обучения
    /// \param textSample флаг наличия вывода сгенерированного
    /// текста, используя последнюю версию модели
    /// \param sampleEvery частота вывода текста
    virtual void train(int iterCount,
                       bool textSample = false,
                       int sampleEvery = 100) = 0;
};

#endif // ITRAINER_H
