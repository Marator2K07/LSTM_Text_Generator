#include "neuralnetworkexception.h"

NeuralNetworkException::NeuralNetworkException(QString message)
    : _message{message.toLocal8Bit()}
{
}

const char *NeuralNetworkException::what() const noexcept
{
    return _message.data();
}
