#ifndef MATRIX2D_H
#define MATRIX2D_H

#include "imatrix.h"

///
/// \brief The Matrix2d class
/// частный случай - двумерная матрица
template<typename T>
class Matrix2d : IMatrix<T>
{
private:
    vector<vector<T>> data;

public:
    Matrix2d();
    Matrix2d(vector<vector<T>> data);
    Matrix2d(initializer_list<initializer_list<T>> list);

public:
    ///
    /// \brief sameShape проверка на полное
    /// соотвествие размеров входящих матриц
    /// \param matrixA первая входящая матрица
    /// \param matrixB вторая входящая матрица
    /// \return флаг соответствия всех размеров
    static bool sameShape(const vector<vector<T>> matrixA,
                          const vector<vector<T>> matrixB);
    ///
    /// \brief canMult проверка количества столбцов
    /// матрицы matrixA и количества строк матрицы matrixB
    /// \param matrixA первая входящая матрица
    /// \param matrixB вторая входящая матрица
    /// \return флаг соответствия размеров столбца и строки
    static bool canMult(const vector<vector<T>> matrixA,
                        const vector<vector<T>> matrixB);

    ///
    /// \brief addition сложение входящих матриц
    /// \param matrixA первая входящая матрица
    /// \param matrixB вторая входящая матрица
    /// \return результирующая матрица
    static vector<vector<T>>
    addition(const vector<vector<T>> matrixA,
             const vector<vector<T>> matrixB);
    ///
    /// \brief addition поэлементное сложение матрицы и числа
    /// \param matrix входящая матрица
    /// \param num число для суммирования
    /// \return результирующая матрица
    static vector<vector<T>>
    addition(const vector<vector<T>> matrix, T num);

    ///
    /// \brief subtraction разность входящих матриц
    /// \param matrixA первая входящая матрица
    /// \param matrixB вторая входящая матрица
    /// \return результирующая матрица
    static vector<vector<T>>
    subtraction(const vector<vector<T>> matrixA,
                const vector<vector<T>> matrixB);
    ///
    /// \brief subtraction поэлементная разность матрицы и числа,
    /// где порядок операндов зависит от reverseOrder
    /// \param matrix входящая матрица
    /// \param num число для разности
    /// \param reverseOrder порядок операндов
    /// \return результирующая матрица
    static vector<vector<T>>
    subtraction(const vector<vector<T>> matrix,
                T num, bool reverseOrder = false);

    ///
    /// \brief multiplication матричное умножение
    /// \param matrixA первая входящая матрица
    /// \param matrixB вторая входящая матрица
    /// \return результирующая матрица
    static vector<vector<T>>
    multiplication(const vector<vector<T>> matrixA,
                   const vector<vector<T>> matrixB);
    ///
    /// \brief simplifiedMult упрощенное поэлементное умножение
    /// \param matrixA первая входящая матрица
    /// \param matrixB вторая входящая матрица
    /// \return результирующая матрица
    static vector<vector<T>>
    simplifiedMult(const vector<vector<T>> matrixA,
                   const vector<vector<T>> matrixB);
    ///
    /// \brief multiplication умножение матрицы на число
    /// \param matrix входящая матрица
    /// \param num мультипликатор умножения
    /// \return увеличенная в num раз матрица
    static vector<vector<T>>
    multiplication(const vector<vector<T>> matrix, T num);

    ///
    /// \brief transposition транспонирование матрицы
    /// \param matrix входящая матрица
    /// \return транспонированная от входной матрица
    static vector<vector<T>>
    transposition(const vector<vector<T>> matrix);

    ///
    /// \brief floorM поэлементное округление матрицы
    /// \param matrix входящая матрица
    /// \param multiplier мультипликатор округления (100,1000 и тд)
    static void floorM(vector<vector<T>> &matrix, int multiplier);

    ///
    /// \brief clip обрезка значений матрицы по границе
    /// \param matrix входящая матрица
    /// \param leftBorder граница обрезки
    /// \return обрезанная по границам [leftBorder, 1-leftBorder] матрица
    static vector<vector<T>> clip(const vector<vector<T>> matrix,
                                  T leftBorder);

    ///
    /// \brief logn нахождение логарифма каждого элемента матрицы
    /// \param matrix входящая матрица
    /// \return матрица с логарифмами элементов входной матрицы
    static vector<vector<T>> logn(const vector<vector<T>> matrix);

    ///
    /// \brief totalSum нахождение суммы всех элементов матрицы
    /// \param matrix входящая матрица
    /// \return сумма всех элементов входной матрицы
    static T totalSum(const vector<vector<T>> matrix);
};

#endif // MATRIX2D_H
