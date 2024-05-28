#ifndef LOSSACTIVATIONFUNCTIONS_H
#define LOSSACTIVATIONFUNCTIONS_H

#include <vector>
#include <cmath>

using namespace std;

///
/// \brief The LossActivationFunctions class
/// для определения функций активации
class LossActivationFunctions
{
public:
    ///
    /// \brief softmax многопеременная логистическая функция
    /// \param p вектор вероятностей(прогнозов)
    static vector<double> softmax(const vector<double> p);
};

#endif // LOSSACTIVATIONFUNCTIONS_H
