#include "simplenum.h"

SimpleNum::SimpleNum(double num)
    : num_{num}
{
}

double SimpleNum::num() const
{
    return num_;
}

Num_Type SimpleNum::type() const
{
    return Num_Type::Simple;
}
