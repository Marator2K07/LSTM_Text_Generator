#ifndef TEXTEMBEDDINGEXCEPTION_H
#define TEXTEMBEDDINGEXCEPTION_H

#include <exception>
#include <QString>
#include <QByteArray>

using namespace std;

///
/// \brief The MatrixException class
/// исключений, связанных с текстовым эмбеддингом
class TextEmbeddingException : public exception
{
private:
    QByteArray _message;

public:
    TextEmbeddingException(QString message = "Error not described");

public:
    // exception interface
    const char *what() const noexcept override;
};

#endif // TEXTEMBEDDINGEXCEPTION_H
