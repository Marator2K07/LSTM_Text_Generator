#include "matrixexception.h"

MatrixException::MatrixException(QString message)
    : _message{message.toLocal8Bit()}
{
}

const char *MatrixException::what() const noexcept
{
    return _message.data();
}
