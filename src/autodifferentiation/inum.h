#ifndef INUM_H
#define INUM_H

#include <QString>

///
/// \brief The Num_Type enum
enum class Num_Type {
    Simple = 0,
    WithGradient
};

///
/// \brief The Num class
/// интерфейс для определения основы какого-то
/// абстрактного числа с плавающей точкой
class INum
{
public:
    virtual double num() const = 0;
    virtual Num_Type type() const = 0;
    virtual ~INum() = default;
};

#endif // INUM_H
