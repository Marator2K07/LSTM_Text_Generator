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

    ///
    /// \brief batchSoftmax расширенная версия softmax
    /// для взаимодействия с партией предсказаний
    /// \param prediction партия предсказаний
    static vector<vector<double>>
        batchSoftmax(const vector<vector<double>> predictions);
};

#endif // LOSSACTIVATIONFUNCTIONS_H
