#ifndef IMATRIX_H
#define IMATRIX_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "matrixexception.h"

using namespace std;

///
/// \brief The IMatrix interface
/// определение функциональности для
/// вложенных векторов - матриц
template<typename T>
class IMatrix
{
public:

public:
    virtual ~IMatrix() {}
};

#endif // IMATRIX_H
