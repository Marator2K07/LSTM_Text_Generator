#ifndef ACTIVATIONFUNCTIONS_H
#define ACTIVATIONFUNCTIONS_H

#include <vector>
#include <cmath>

using namespace std;

///
/// \brief The LossActivationFunctions class
/// для определения функций активации
template<typename T>
class ActivationFunctions
{
public:
    ///
    /// \brief softmax многопеременная логистическая функция
    /// \param prediction вектор вероятностей(прогнозов)
    /// \return обработанный вектор
    static vector<double> softmax(const vector<T> prediction);
};

#endif // ACTIVATIONFUNCTIONS_H
