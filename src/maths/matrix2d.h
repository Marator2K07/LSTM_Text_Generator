#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <imatrix.h>

template<typename T>
class Matrix2D : IMatrix
{
private:
    vector<vector<T>> data;
    int _rows;
    int _cols;

public:
    explicit Matrix2D();

public:
    const int rows();
    const int cols();

    // IMatrix interface
    bool sameShape(const IMatrix *) override;
    IMatrix *addition(IMatrix *) override;
    IMatrix *subtraction(IMatrix *) override;
    IMatrix *multiplication(IMatrix *) override;
    IMatrix *transposition(IMatrix *) override;
};

#endif // MATRIX2D_H
