#ifndef ILOSS_H
#define ILOSS_H

#include <iostream>
#include <vector>

#include "activationfunctions.h"
#include "imatrix.h"
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
    virtual double forward(IMatrix<double> *prediction,
                           IMatrix<double> *target) = 0;
    ///
    /// \brief backward обратный проход работы с потерями
    /// \return градиент для каждого элемента
    /// прогноза относительно потери
    virtual unique_ptr<IMatrix<double>> backward() = 0;

private:
    ///
    /// \brief calcLoss непосредственное вычисление штрафа сети
    /// \return найденная потери сети
    virtual double calcLoss() = 0;
    ///
    /// \brief calcInputGradient непосредственное вычисление
    /// градиента ошибки по входу функции потерь
    /// \return матрица с найденными градиентами
    virtual IMatrix<double> *calcInputGradient() = 0;
};

#endif // ILOSS_H
