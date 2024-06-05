#include "matrix3d.h"

template<typename T>
Matrix3d<T>::Matrix3d()
{
}

template<typename T>
Matrix3d<T>::Matrix3d(vector<Matrix2d<T>> data)
    : data{data}
{
}

template<typename T>
Matrix3d<T>::Matrix3d(initializer_list<initializer_list<initializer_list<T>>> list)
{
    for (initializer_list<initializer_list<T>> matrix : list) {
        data.push_back(Matrix2d(matrix));
    }
}

template<typename T>
void Matrix3d<T>::print()
{
    for (Matrix2d<T> matrix : data) {
        matrix.print();
    }
}

{

}
