#ifndef ILOSS_H
#define ILOSS_H

#include <iostream>
#include <vector>

#include "matrix2d.h"
#include "matrix2d.cpp"
#include "activationfunctions.h"
#include "lossexception.h"

using namespace std;

///
/// \brief The ILoss interface
/// определение функционала для вычисления
/// потерь нейронной сети при обучении
class ILoss
{
public:
    ///
    /// \brief forward прямой проход вычисления потерь
    /// \param prediction матрица предсказанных результатов
    /// \param target целевая матрица
    /// \return значение потерь(штрафа) сети
    virtual double forward(vector<vector<double>> prediction,
                           vector<vector<double>> target) = 0;
    ///
    /// \brief backward обратный проход работы с потерями
    /// \return градиент для каждого элемента
    /// прогноза относительно потери
    virtual vector<vector<double>> backward() = 0;

private:
    ///
    /// \brief calculate непосредственное вычисление штрафа сети
    virtual double calculate() = 0;
    ///
    /// \brief inputGradient непосредственное вычисление
    /// градиента ошибки по входу функции потерь
    virtual vector<vector<double>> inputGradient() = 0;
};

#endif // ILOSS_H
