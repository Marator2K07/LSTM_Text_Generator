#include "matrix2d.h"

template<typename T>
Matrix2D<T>::Matrix2D()
{
}

template<typename T>
const int Matrix2D<T>::rows()
{
    return _rows;
}

template<typename T>
const int Matrix2D<T>::cols()
{
    return _cols;
}

template<typename T>
bool Matrix2D<T>::sameShape(const IMatrix *)
{

}

template<typename T>
IMatrix *Matrix2D<T>::addition(IMatrix *)
{

}

template<typename T>
IMatrix *Matrix2D<T>::subtraction(IMatrix *)
{

}

template<typename T>
IMatrix *Matrix2D<T>::multiplication(IMatrix *)
{

}

template<typename T>
IMatrix *Matrix2D<T>::transposition(IMatrix *)
{

}
