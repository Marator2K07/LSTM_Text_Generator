#include "textembeddingexception.h"

TextEmbeddingException::TextEmbeddingException(QString message)
    : _message{message.toLocal8Bit()}
{
}

const char *TextEmbeddingException::what() const noexcept
{
    return _message.data();
}
