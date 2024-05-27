#include "lossactivationfunctions.h"

vector<double> LossActivationFunctions::softmax(const vector<double> p)
{
    // сначала находим общий знаменатель
    double denominator = 0;
    for (const double value : p) {
        denominator += exp(value);
    }
    // следующим проходом составляем обработанный вектор
    vector<double> result;
    for (const double value : p) {
        result.push_back(exp(value)/denominator);
    }
    return result;
}
