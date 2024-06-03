#ifndef LOSSEXCEPTION_H
#define LOSSEXCEPTION_H

#include <exception>
#include <QString>
#include <QByteArray>

using namespace std;

///
/// \brief The MatrixException class
/// исключений, связанных с потерями
class LossException : exception
{
private:
    QByteArray _message;

public:
    LossException(QString message = "Error not described");

public:
    // exception interface
    const char *what() const noexcept override;
};

#endif // LOSSEXCEPTION_H
