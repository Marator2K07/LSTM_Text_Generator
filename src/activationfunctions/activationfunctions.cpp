#include "activationfunctions.h"

template<typename T>
vector<double> ActivationFunctions<T>::softmaxRow(vector<T> row)
{
    // сначала находим общий знаменатель
    double denominator = 0;
    for (const double value : row) {
        denominator += exp(value);
    }
    // следующим проходом составляем обработанный вектор
    vector<double> result;
    for (const double value : row) {
        result.push_back(exp(value)/denominator);
    }

    return result;
}
