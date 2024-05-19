#include "numwithgradient.h"

NumWithGradient::NumWithGradient(QVariant num)
    : num{num}
    , gradient{nullptr}
    , depends_on{vector}
{
}
