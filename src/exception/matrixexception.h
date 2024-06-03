#ifndef MATRIXEXCEPTION_H
#define MATRIXEXCEPTION_H

#include <exception>
#include <QString>
#include <QByteArray>

using namespace std;

///
/// \brief The MatrixException class
/// исключений, связанных с матрицами
class MatrixException : exception
{
private:
    QByteArray _message;

public:
    MatrixException(QString message = "Error not described");

public:
    // exception interface
    const char *what() const noexcept override;
};

#endif // MATRIXEXCEPTION_H
