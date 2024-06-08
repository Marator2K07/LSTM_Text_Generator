#include "activationfunctions.h"

vector<double> ActivationFunctions::softmax(const vector<double> prediction)
{
    // сначала находим общий знаменатель
    double denominator = 0;
    for (const double value : prediction) {
        denominator += exp(value);
    }
    // следующим проходом составляем обработанный вектор
    vector<double> result;
    for (const double value : prediction) {
        result.push_back(exp(value)/denominator);
    }
    return result;
}
