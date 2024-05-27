#ifndef MATRIX_H
#define MATRIX_H

///
/// \brief The Matrix interface
/// определение функциональности
/// для матриц какой-либо размерности
class Matrix
{
public:
    virtual Matrix *addition(Matrix *) = 0;
    virtual Matrix *subtraction(Matrix *) = 0;
    virtual Matrix *multiplication(Matrix *) = 0;
    virtual Matrix *transposition(Matrix *) = 0;
};

#endif // MATRIX_H
