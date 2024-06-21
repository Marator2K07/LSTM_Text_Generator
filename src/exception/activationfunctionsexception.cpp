#include "activationfunctionsexception.h"

ActivationFunctionsException::ActivationFunctionsException(QString message)
    : _message{message.toLocal8Bit()}
{
}

const char *ActivationFunctionsException::what() const noexcept
{
    return _message.data();
}
