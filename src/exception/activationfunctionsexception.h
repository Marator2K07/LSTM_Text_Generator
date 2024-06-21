#ifndef ACTIVATIONFUNCTIONSEXCEPTION_H
#define ACTIVATIONFUNCTIONSEXCEPTION_H

#include <exception>
#include <QString>
#include <QByteArray>

using namespace std;

///
/// \brief The ActivationFunctionsException class
/// исключений, связанных с функциями активации
class ActivationFunctionsException : public exception
{
private:
    QByteArray _message;

public:
    ActivationFunctionsException(QString message = "Error not described");

public:
    // exception interface
    const char *what() const noexcept override;
};

#endif // ACTIVATIONFUNCTIONSEXCEPTION_H
