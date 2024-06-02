#ifndef MATRIX3D_H
#define MATRIX3D_H

#include <vector>

using namespace std;

///
/// \brief The Matrix3d class
/// определение основных типов операций
/// над элементами трехмерного матричного типа
template<typename T>
class Matrix3d
{
public:
    // соответствие матриц
    static bool sameShape(const vector<vector<vector<T>>> matrixA,
                          const vector<vector<vector<T>>> matrixB);

    // сумма матриц (или матрицы и числа)
    static vector<vector<vector<T>>>
        addition(const vector<vector<vector<T>>> matrixA,
                 const vector<vector<vector<T>>> matrixB);
    static vector<vector<vector<T>>>
        addition(const vector<vector<vector<T>>> matrix, T num);

    // разность матриц (или матрицы и числа)
    static vector<vector<vector<T>>>
        subtraction(const vector<vector<vector<T>>> matrixA,
                    const vector<vector<vector<T>>> matrixB);
    static vector<vector<vector<T>>>
        subtraction(const vector<vector<vector<T>>> matrix, T num);

    // умножение матриц (или матрицы и числа)
    static vector<vector<vector<T>>>
        multiplication(const vector<vector<vector<T>>> matrixA,
                       const vector<vector<vector<T>>> matrixB);
    static vector<vector<vector<T>>>
        multiplication(const vector<vector<vector<T>>> matrix, T num);

    // транспозиция матрицы
    static vector<vector<vector<T>>>
        transposition(const vector<vector<vector<T>>> matrix);
};

#endif // MATRIX3D_H
