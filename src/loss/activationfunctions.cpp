#include "activationfunctions.h"

vector<double> ActivationFunctions::softmax(const vector<double> prediction)
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

unique_ptr<IMatrix<double>>
ActivationFunctions::batchSoftmax(const IMatrix<double> *predictions)
{
    // построчно обрабатываем предсказания
    vector<vector<double>> result;
    for (const vector<double> &p : predictions) {
        result.push_back(softmax(p));
    }
    return result;
}
