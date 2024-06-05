#ifndef MATRIX3D_H
#define MATRIX3D_H

#include "matrix2d.h"

///
/// \brief The Matrix3d class
/// частный случай - трехмерная матрица
/// важное замечание, данный класс является
/// надстройкой над классом Matrix2d
template<typename T>
class Matrix3d : IMatrix<T>
{
private:
    vector<Matrix2d<T>> data;

public:
    Matrix3d();
    Matrix3d(vector<Matrix2d<T>> data);
    Matrix3d(initializer_list<initializer_list<initializer_list<T>>> list);

};

#endif // MATRIX3D_H
