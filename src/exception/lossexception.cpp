#include "lossexception.h"

LossException::LossException(QString message)
    : _message{message.toLocal8Bit()}
{
}

const char *LossException::what() const noexcept
{
    return _message.data();
}
