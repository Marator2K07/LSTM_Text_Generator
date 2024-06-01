#include <matrix2d.h>

template<typename T>
bool Matrix2d<T>::sameShape(const vector<vector<T>> matrixA,
                            const vector<vector<T>> matrixB)
{
    return matrixA.size() == matrixB.size() &&
           matrixA[0].size() == matrixB[0].size();
}

template<typename T>
bool Matrix2d<T>::canMult(const vector<vector<T>> matrixA,
                          const vector<vector<T>> matrixB)
{
    return matrixA[0].size() != matrixB.size();
}

template<typename T>
vector<vector<T>> Matrix2d<T>::addition(const vector<vector<T>> matrixA,
                                        const vector<vector<T> > matrixB)
{

}

template<typename T>
vector<vector<T>> Matrix2d<T>::addition(const vector<vector<T>> matrix,
                                        T num)
{

}

template<typename T>
vector<vector<T>> Matrix2d<T>::subtraction(const vector<vector<T>> matrixA,
                                           const vector<vector<T>> matrixB)
{

}

template<typename T>
vector<vector<T>> Matrix2d<T>::subtraction(const vector<vector<T>> matrix,
                                           T num)
{

}

template<typename T>
vector<vector<T>> Matrix2d<T>::multiplication(const vector<vector<T>> matrixA,
                                              const vector<vector<T>> matrixB)
{
    // подготовка
    vector<vector<T>> result;
    if (canMult(matrixA, matrixB)) {
        return result;
    }
    int index = 0;
    // заполнение выходной матрицы
    for (const vector<T> rowA : matrixA) {
        result.push_back(vector<T>());
        int innerIndex = 0;
        // вычисление значений строки результирующей матрицы
        for (int indexB = 0; indexB < matrixB[0].size(); ++indexB) {
            // вычисление значения ячейки
            T stepRes = 0;
            for (int indexA = 0; indexA < rowA.size(); ++indexA) {
                stepRes += matrixB[indexA][innerIndex] * rowA[indexA];
            }
            result[index].push_back(stepRes);
            innerIndex++;
        }
        index++;
    }

    return result;
}

template<typename T>
vector<vector<T>> Matrix2d<T>::multiplication(const vector<vector<T>> matrix,
                                              T num)
{
    // подготовка
    vector<vector<T>> result;
    int index = 0;
    // заполнение выходной матрицы
    for (const vector<T> row : matrix) {
        result.push_back(vector<T>());
        for (const T value : row) {
            result[index].push_back(value * num);
        }
        index++;
    }

    return result;
}

template<typename T>
vector<vector<T>> Matrix2d<T>::transposition(const vector<vector<T>> matrix)
{

}

template<typename T>
void Matrix2d<T>::floorM(vector<vector<T>> &matrix, int multDegree)
{
    for (vector<T> &row : matrix) {
        for (T &value : row) {
            value = floor(value * multDegree) / multDegree;
        }
    }
}

template<typename T>
vector<vector<T>> Matrix2d<T>::clip(const vector<vector<T>> matrix,
                                    T leftBorder)
{
    // подготовка
    vector<vector<T>> result;
    int index = 0;
    T rightBorder = 1 - leftBorder;
    // заполнение результирующей матрицы
    for (const vector<T> row : matrix) {
        result.push_back(vector<T>());
        for (const T value : row) {
            T newValue;
            if (value <= leftBorder) {
                newValue = leftBorder;
            } else if (value >= rightBorder) {
                newValue = rightBorder;
            } else {
                newValue = value;
            }
            result[index].push_back(newValue);
        }
        index++;
    }

    return result;
}
