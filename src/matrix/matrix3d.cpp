#include "matrix3d.h"

template<typename T>
Matrix3D<T>::Matrix3D()
    : _size{0}
    , _rows{0}
    , _cols{0}
{
}

template<typename T>
const int Matrix3D<T>::rows()
{
    return _rows;
}

template<typename T>
const int Matrix3D<T>::cols()
{
    return _cols;
}

template<typename T>
const int Matrix3D<T>::size()
{
    return _size;
}
