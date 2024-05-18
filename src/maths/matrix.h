#ifndef MATRIX_H
#define MATRIX_H

#include <QObject>

class Matrix : public QObject
{
    Q_OBJECT
public:
    explicit Matrix(QObject *parent = nullptr);

signals:

};

#endif // MATRIX_H
