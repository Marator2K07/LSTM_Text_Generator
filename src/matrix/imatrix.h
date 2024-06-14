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
/// \brief The Dimensions enum
/// определение количества измерений матрицы как типа
enum class Dimensions {
    TWO, THREE
};

///
/// \brief The IMatrix interface
/// определение функциональности для
/// вложенных векторов - матриц
template<typename T>
class IMatrix
{
private:
    ///
    /// \brief doOperation проведение заранее указанной операции с матрицей
    /// \param matrix входная матрица для операции
    /// \return результирующая матрица
    virtual unique_ptr<IMatrix<T>> doOperation(const IMatrix<T> *matrix) = 0;
    ///
    /// \brief doOperation проведение заранее указаной операции с числом
    /// \param num входное число для проведения операции
    /// \param reverseOrder порядок операндов
    /// \return результирующая матрица
    virtual unique_ptr<IMatrix<T>> doOperation(const T num,
                                               bool reverseOrder = false) = 0;

public:
    ///
    /// \brief type вывод количества измерений матрицы
    /// \return перечисление Dimensions
    virtual Dimensions type() const = 0;
    ///
    /// \brief data универсальный геттер
    /// \return данные вектора внутри обертки матрицы
    virtual QVariant data() const = 0;
    ///
    /// \brief sizes нахождение размеров матрицы
    /// \return вектор с размерами матрицы ('глубина'-высота-ширина)
    virtual vector<unsigned long long> sizes() const = 0;
    ///
    /// \brief sameShape проверка на полное
    /// соотвествие размеров этой и другой матрицы
    /// \param other другая матрица
    /// \return флаг соответствия всех размеров
    virtual bool sameShape(const IMatrix<T> *matrix) = 0;
    ///
    /// \brief addition сложение элементов текущей и другой матрицы
    /// \param other другая матрицы для сложения
    /// \return результирующая матрица
    virtual unique_ptr<IMatrix<T>> addition(const IMatrix<T> *matrix) = 0;
    ///
    /// \brief addition поэлементное сложение матрицы и числа
    /// \param num число для сложения
    /// \return результирующая матрица
    virtual unique_ptr<IMatrix<T>> addition(T num) = 0;
    ///
    /// \brief subtraction вычитание элементов текущей и другой матриц
    /// \param other другая матрицы для текущей операции
    /// \return результирующая матрица
    virtual unique_ptr<IMatrix<T>> subtraction(const IMatrix<T> *matrix) = 0;
    ///
    /// \brief subtraction поэлементная разность матрицы и числа
    /// (или числа и матрицы), где порядок операндов зависит от reverseOrder
    /// \param num число для разности
    /// \param reverseOrder порядок операндов
    /// \return результирующая матрица
    virtual unique_ptr<IMatrix<T>> subtraction(T num, bool reverseOrder = false) = 0;
    ///
    /// \brief simplifiedMult упрощенное поэлементное умножение элементов матриц
    /// \param other другая матрицы для операции
    /// \return результирующая матрица
    virtual unique_ptr<IMatrix<T>> simplifiedMult(const IMatrix<T> *matrix) = 0;
    ///
    /// \brief multiplication умножение матрицы на число
    /// \param num мультипликатор умножения
    /// \return увеличенная в num раз матрица
    virtual unique_ptr<IMatrix<T>> multiplication(T num) = 0;
    ///
    /// \brief dividing поэлементное деление матрицы и числа(или числа
    /// и матрицы), где порядок порядок операндов зависит от reverseOrder
    /// \param num число для деления
    /// \param reverseOrder порядок операндов
    /// \return результирующая матрица
    virtual unique_ptr<IMatrix<T>> dividing(T num, bool reverseOrder = false) = 0;
    ///
    /// \brief floorM округление текущей матрицы до num цифр после запятой
    /// \param num количество цифр после запятой
    virtual void floorM(T num) = 0;
    ///
    /// \brief clipM обрезка значений текущей матрицы
    /// \param leftBorder левая граница обрезки
    /// \param rightBorder правая граница обрезки
    /// \return обрезанная по границам [leftBorder, rightBorder] матрица
    virtual unique_ptr<IMatrix<T>> clipM(T leftBorder, T rightBorder) = 0;
    ///
    /// \brief lognM нахождение алгоритма каждого элемента матрицы
    /// \return матрица с найденными алгоритмами
    virtual unique_ptr<IMatrix<T>> lognM() = 0;
    ///
    /// \brief totalSum нахождение суммы всех элементов матрицы
    /// \return сумма всех элементов входной матрицы
    virtual T totalSum() = 0;

public:
    virtual ~IMatrix() {}
};

#endif // IMATRIX_H
