#ifndef NUMWITHGRADIENT_H
#define NUMWITHGRADIENT_H

#include <vector>
#include "num.h"

using namespace std;

class NumWithGradient : Num
{
private:
    double num_;
    vector<NumWithGradient> depends_on;
    double gradient_;
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
                             vector<NumWithGradient> depends_on
                                = vector<NumWithGradient>{},
                             QString creation_op = "");

public:
    NumWithGradient operator+(Num *other);
    NumWithGradient operator*(Num *other);
    double gradient();

    // Num interface
    double num() const override;
    Num_Type type() const override;
};

#endif // NUMWITHGRADIENT_H
