#ifndef NEURALNETWORKEXCEPTION_H
#define NEURALNETWORKEXCEPTION_H

#include <exception>
#include <QString>
#include <QByteArray>

using namespace std;

///
/// \brief The NeuralNetworkException class
/// исключений, связанных с работой нейронной сети
class NeuralNetworkException : public exception
{
private:
    QByteArray _message;

public:
    NeuralNetworkException(QString message = "Error not described");

public:
    // exception interface
    const char *what() const noexcept override;
};

#endif // NEURALNETWORKEXCEPTION_H
