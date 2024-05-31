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
