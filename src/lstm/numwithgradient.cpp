#include "numwithgradient.h"

NumWithGradient::NumWithGradient(double num)
    : num_{num}
    , gradient{0}
    , creation_op{""}
{
}

NumWithGradient NumWithGradient::ensureNum(Num *num)
{
    switch (num->type()) {
    case Num_Type::Simple:
        return NumWithGradient(num->num());
    case Num_Type::WithGradient:
        return *(NumWithGradient*)num;
    default:
        return NumWithGradient(0);
    }
}

double NumWithGradient::num() const
{
    return num_;
}

Num_Type NumWithGradient::type() const
{
    return Num_Type::WithGradient;
}
