#include "matrix.h"

Matrix::Matrix(QObject *parent)
    : QObject{parent}
    , sizes{0,0,0}
{
}

const int Matrix::width()
{
    return sizes[0];
}

const int Matrix::height()
{
    return sizes[1];
}

const int Matrix::depth()
{
    return sizes[2];
}
