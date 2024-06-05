#ifndef MATRIX3D_H
#define MATRIX3D_H

#include "imatrix.h"

///
/// \brief The Matrix3d class
/// частный случай - трехмерная матрица
template<typename T>
class Matrix3d : IMatrix<T>
{
private:
    vector<vector<vector<T>>> data;

public:
    Matrix3d();
    Matrix3d(vector<vector<vector<T>>> data);
    Matrix3d(initializer_list<initializer_list<initializer_list<T>>> list);

};

#endif // MATRIX3D_H
