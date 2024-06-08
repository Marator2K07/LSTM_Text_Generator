#ifndef ACTIVATIONFUNCTIONS_H
#define ACTIVATIONFUNCTIONS_H

#include <vector>
#include <cmath>

#include "imatrix.h"
#include "matrix2d.h"
#include "matrix3d.h"

using namespace std;

///
/// \brief The LossActivationFunctions class
/// для определения функций активации
class ActivationFunctions
{
public:
    ///
    /// \brief softmax многопеременная логистическая функция
    /// \param prediction вектор вероятностей(прогнозов)
    /// \return обработанный вектор
    static vector<double> softmax(const vector<double> prediction);

    ///
    /// \brief batchSoftmax расширенная версия softmax
    /// для взаимодействия с матрицей предсказаний
    /// \param prediction партия предсказаний
    /// \return партия обработанных векторов(матрица)
    static unique_ptr<IMatrix<double>>
    batchSoftmax(const IMatrix<double> *predictions);
};

#endif // ACTIVATIONFUNCTIONS_H
