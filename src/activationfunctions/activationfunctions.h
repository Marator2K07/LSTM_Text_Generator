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
template<typename T>
class ActivationFunctions
{
private:
    ///
    /// \brief softmaxRow нахождение softmax для строки(вектора) значений
    /// \param row входящий вектор значений
    /// \return обработанный softmax вектор
    static vector<double> softmaxRow(vector<T> row);

public:
    ///
    /// \brief sigmoid гладкая монотонная возрастающая нелинейная функция,
    /// имеющая форму буквы «S» для «сглаживания» значений некоторой величины.
    /// \param matrix матрица входящих значений для сглаживания
    /// \return результирующая матрица
    static unique_ptr<IMatrix<double>> sigmoid(const IMatrix<T> *matrix);
    ///
    /// \brief softmax многопеременная логистическая функция
    /// \param matrix вектор вероятностей(прогнозов)
    /// \return обработанный вектор
    static unique_ptr<IMatrix<double>> softmax(const IMatrix<T> *matrix);
};

#endif // ACTIVATIONFUNCTIONS_H
