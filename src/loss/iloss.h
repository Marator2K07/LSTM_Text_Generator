#ifndef ILOSS_H
#define ILOSS_H

#include "matrix.h"

///
/// \brief The ILoss interface
/// определение функционала для вычисления
/// потерь нейронной сети при обучении
class ILoss
{
public:
    ILoss();
    ///
    /// \brief forward подготовка вычисления значения потерь(штрафа)
    /// \param prediction матрица предсказанных результатов
    /// \param target целевая матрица
    virtual double forward(Matrix *prediction, Matrix *target) = 0;
    ///
    /// \brief backward подготовка возврата назад градиента для
    /// каждого элемента прогноза относительно потери
    virtual Matrix *backward() = 0;

private:
    ///
    /// \brief calculate непосредственное вычисление штрафа сети
    virtual double calculate() = 0;
    ///
    /// \brief inputGradient непосредственное вычисление
    /// градиента ошибки по входу функции потерь
    virtual Matrix *inputGradient() = 0;
};

#endif // ILOSS_H
