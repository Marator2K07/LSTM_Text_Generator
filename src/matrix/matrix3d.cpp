#include "matrix3d.h"

template<typename T>
Matrix3d<T>::Matrix3d()
{
}

template<typename T>
Matrix3d<T>::Matrix3d(vector<Matrix2d<T>> data)
    : _data{data}
{
}

template<typename T>
Matrix3d<T>::Matrix3d(initializer_list<initializer_list<initializer_list<T>>> list)
{
    for (initializer_list<initializer_list<T>> matrix : list) {
        _data.push_back(Matrix2d(matrix));
    }
}

template<typename T>
void Matrix3d<T>::print()
{
    for (Matrix2d<T> matrix : _data) {
        matrix.print();
    }
}

template<typename T>
const vector<Matrix2d<T>> Matrix3d<T>::data()
{
    return _data;
}

{

}
