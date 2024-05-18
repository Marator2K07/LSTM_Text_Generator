#ifndef MATRIX3D_H
#define MATRIX3D_H

#include <QObject>
#include <constants.h>
#include <vector>
#include <array>

using namespace std;

template<typename T>
class Matrix3D : public QObject
{
    Q_OBJECT
private:
    int sizes[MAX_MATRIX_SIZE];

public:
    explicit Matrix3D(QObject *parent = nullptr);

public:
    const int width();
    const int height();
    const int depth();

signals:

};

#endif // MATRIX3D_H
