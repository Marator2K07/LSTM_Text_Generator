#ifndef MATRIX3D_H
#define MATRIX3D_H

#include <constants.h>
#include <vector>

using namespace std;

template<typename T>
class Matrix3D
{
private:
    vector<vector<vector<T>>> data;
    int _rows;
    int _cols;
    int _size;

public:
    explicit Matrix3D();

public:
    const int rows();
    const int cols();
    const int size();
};

#endif // MATRIX3D_H
