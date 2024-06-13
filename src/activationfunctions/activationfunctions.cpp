#include "activationfunctions.h"

template<typename T>
vector<double> ActivationFunctions<T>::softmax(const vector<T> prediction)
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
