#ifndef IMATRIX_H
#define IMATRIX_H

#include <memory>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "matrixexception.h"

using namespace std;

///
/// \brief The IMatrix interface
/// определение функциональности для
/// вложенных векторов - матриц
template<typename T>
class IMatrix
{
public:
    ///
    /// \brief sameShape проверка на полное
    /// соотвествие размеров этой и другой матрицы
    /// \param other другая матрица
    /// \return флаг соответствия всех размеров
    virtual bool sameShape(const IMatrix<T> *other) = 0;
    ///
    /// \brief addition сложение элементов текущей и другой матрицы
    /// \param other другая матрицы для сложения
    /// \return результирующая матрица
    virtual unique_ptr<IMatrix<T>> addition(const IMatrix<T> *other) = 0;

public:
    virtual ~IMatrix() {}
};

#endif // IMATRIX_H
