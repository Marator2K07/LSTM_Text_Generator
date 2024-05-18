#ifndef MATRIX_H
#define MATRIX_H

#include <QObject>
#include <constants.h>

class Matrix : public QObject
{
    Q_OBJECT
private:
    int sizes[MAX_MATRIX_SIZE];

public:
    explicit Matrix(QObject *parent = nullptr);
    const int width();
    const int height();
    const int depth();

signals:

};

#endif // MATRIX_H
