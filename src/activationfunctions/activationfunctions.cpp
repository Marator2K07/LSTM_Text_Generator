#include "activationfunctions.h"

template<typename T>
unique_ptr<IMatrix<double>> ActivationFunctions<T>::sigmoid(const IMatrix<T> *matrix)
{

}

template<typename T>
unique_ptr<IMatrix<double>> ActivationFunctions<T>::softmax(const IMatrix<T> *matrix)
{
    // подготовка
    Matrix2d<double> result = new Matrix2d(matrix->data());
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
