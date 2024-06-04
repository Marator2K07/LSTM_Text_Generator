#ifndef SIMPLENUM_H
#define SIMPLENUM_H

#include "num.h"

///
/// \brief The SimpleNum class
/// формально класс обертка для простого числа
/// с плавающей точкой без "добавок"
class SimpleNum : Num
{
private:
    double num_;

public:
    SimpleNum(double num);

    // Num interface
public:
    double num() const override;
    Num_Type type() const override;
};

#endif // SIMPLENUM_H
