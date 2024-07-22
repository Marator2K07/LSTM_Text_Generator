#ifndef TRAINEREXCEPTION_H
#define TRAINEREXCEPTION_H

#include <exception>
#include <QString>
#include <QByteArray>

using namespace std;

///
/// \brief The TrainerException class
/// иключений, связанных с обучением
/// моделей нейронных сетей
class TrainerException : public exception
{
private:
    QByteArray _message;

public:
    TrainerException(QString message = "Error not described");

public:
    // exception interface
    const char *what() const noexcept override;
};

#endif // TRAINEREXCEPTION_H
