#include "matrix3d.h"

Matrix3D::Matrix(QObject *parent)
    : QObject{parent}
    , sizes{0,0,0}
{
}

const int Matrix3D::width()
{
    return sizes[0];
}

const int Matrix3D::height()
{
    return sizes[1];
}

const int Matrix3D::depth()
{
    return sizes[2];
}
