#include "trainerexception.h"

TrainerException::TrainerException(QString message)
    : _message{message.toLocal8Bit()}
{
}

const char *TrainerException::what() const noexcept
{
    return _message.data();
}
