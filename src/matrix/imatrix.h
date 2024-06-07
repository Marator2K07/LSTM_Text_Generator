#ifndef IMATRIX_H
#define IMATRIX_H

#include <memory>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <QVariant>

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
    /// \brief data универсальный геттер
    /// \return данные вектора внутри обертки матрицы
    virtual QVariant data() const = 0;
    ///
    /// \brief sizes нахождение размеров матрицы
    /// \return вектор с размерами матрицы ('глубина'-высота-ширина)
    virtual vector<int> sizes() const = 0;
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
    ///
    /// \brief addition поэлементное сложение матрицы и числа
    /// \param num число для сложения
    /// \return результирующая матрица
    virtual unique_ptr<IMatrix<T>> addition(T num) = 0;

public:
    virtual ~IMatrix() {}
};

#endif // IMATRIX_H
