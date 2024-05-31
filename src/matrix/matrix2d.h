#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <constants.h>
#include <vector>

using namespace std;

///
/// \brief The Matrix2d class
/// определение основных типов операций
/// над элементами двумерного матричного типа
template<typename T>
class Matrix2d
{
public:
    // соответствие матриц
    static bool sameShape(const vector<vector<T>> matrixA,
                          const vector<vector<T>> matrixB);
    static bool canMult(const vector<vector<T>> matrixA,
                        const vector<vector<T>> matrixB);

    // сумма матриц (или матрицы и числа)
    static vector<vector<T>>
        addition(const vector<vector<T>> matrixA,
                 const vector<vector<T>> matrixB);    
    static vector<vector<T>>
        addition(const vector<vector<T>> matrix, T num);

    // разность матриц (или матрицы и числа)
    static vector<vector<T>>
        subtraction(const vector<vector<T>> matrixA,
                    const vector<vector<T>> matrixB);    
    static vector<vector<T>>
        subtraction(const vector<vector<T>> matrix, T num);

    // умножение матриц (или матрицы и числа)
    static vector<vector<T>>
        multiplication(const vector<vector<T>> matrixA,
                       const vector<vector<T>> matrixB);    
    static vector<vector<T>>
        multiplication(const vector<vector<T>> matrix, T num);

    // транспозиция матрицы
    static vector<vector<T>>
        transposition(const vector<vector<T>> matrix);

    // обрезка значений по границе [leftBorder, 1-leftBorder]
    static vector<vector<T>> clip(const vector<vector<T>> matrix,
                                  T leftBorder);
};

#endif // MATRIX2D_H
