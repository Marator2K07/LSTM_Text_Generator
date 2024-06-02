#ifndef ILOSS_H
#define ILOSS_H

#include <vector>
#include "matrix2d.h"
#include "matrix2d.cpp"
#include "activationfunctions.h"

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
    /// (подготовка вычисления значения потерь(штрафа) + вычисление)
    /// \param prediction матрица предсказанных результатов
    /// \param target целевая матрица
    virtual double forward(vector<vector<double>> prediction,
                           vector<vector<double>> target) = 0;
    ///
    /// \brief backward обратный проход работы с потерями
    /// (подготовка возврата назад градиента для каждого
    /// элемента прогноза относительно потери)
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
