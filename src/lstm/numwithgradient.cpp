#include "numwithgradient.h"

NumWithGradient::NumWithGradient(double num)
    : num_{num}
    , gradient{0}
    , creation_op{""}
{
}

double NumWithGradient::num() const
{
    return num_;
}

Num_Type NumWithGradient::type() const
{
    return Num_Type::WithGradient;
}
