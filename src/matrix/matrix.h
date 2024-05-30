#ifndef MATRIX_H
#define MATRIX_H

#include <constants.h>
#include <vector>

using namespace std;

///
/// \brief The Matrix class
/// определение основных типов операций
/// над элементами матричного типа (вложенными векторами)
template<typename T>
class Matrix
{
public:
    // соответствие матриц
    static bool sameShape(const vector<vector<T>> matrixA,
                          const vector<vector<T>> matrixB);
    static bool sameShape(const vector<vector<vector<T>>> matrixA,
                          const vector<vector<vector<T>>> matrixB);

    // сумма матриц
    static vector<vector<T>>
        addition(const vector<vector<T>> matrixA,
                 const vector<vector<T>> matrixB);
    static vector<vector<vector<T>>>
        addition(const vector<vector<vector<T>>> matrixA,
                 const vector<vector<vector<T>>> matrixB);

    // разность матриц
    static vector<vector<T>>
        subtraction(const vector<vector<T>> matrixA,
                    const vector<vector<T>> matrixB);
    static vector<vector<vector<T>>>
        subtraction(const vector<vector<vector<T>>> matrixA,
                    const vector<vector<vector<T>>> matrixB);

    // умножение матриц
    static vector<vector<T>>
        multiplication(const vector<vector<T>> matrixA,
                       const vector<vector<T>> matrixB);
    static vector<vector<vector<T>>>
        multiplication(const vector<vector<vector<T>>> matrixA,
                       const vector<vector<vector<T>>> matrixB);

    // транспозиция матриц
    static vector<vector<T>>
        transposition(const vector<vector<T>> matrixA,
                      const vector<vector<T>> matrixB);
    static vector<vector<vector<T>>>
        transposition(const vector<vector<vector<T>>> matrixA,
                      const vector<vector<vector<T>>> matrixB);
};

#endif // MATRIX_H
