#ifndef NUMWITHGRADIENT_H
#define NUMWITHGRADIENT_H

#include <vector>

#include "num.h"

using namespace std;

class NumWithGradient : Num
{
private:
    double num_;
    double gradient;
    vector<double> depends_on;
    QString creation_op;

private:
    ///
    /// \brief ensureNum вспомогательный метод для
    /// превращения любого числа на входе в число
    /// с градиентом и его возвращение
    /// \param num - пришедшее абстрактное число
    /// с градиентом или без
    NumWithGradient ensureNum(Num *num);

public:
    explicit NumWithGradient(double num,
                             vector<double> depends_on = vector<double>{},
                             QString creation_op = "");

public:
    // Num interface
    double num() const override;
    Num_Type type() const override;
};

#endif // NUMWITHGRADIENT_H
