#ifndef IMATRIX_H
#define IMATRIX_H

#include <constants.h>
#include <vector>

using namespace std;

///
/// \brief The IMatrix interface
/// определение функциональности
/// для матриц какой-либо размерности
class IMatrix
{
public:
    virtual bool sameShape(const IMatrix *) = 0;
    virtual IMatrix *addition(IMatrix *) = 0;
    virtual IMatrix *subtraction(IMatrix *) = 0;
    virtual IMatrix *multiplication(IMatrix *) = 0;
    virtual IMatrix *transposition(IMatrix *) = 0;
};

#endif // IMATRIX_H
