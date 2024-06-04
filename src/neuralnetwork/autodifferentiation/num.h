#ifndef NUM_H
#define NUM_H

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
class Num
{
public:
    virtual double num() const = 0;
    virtual Num_Type type() const = 0;
    virtual ~Num() = default;
};

#endif // NUM_H
