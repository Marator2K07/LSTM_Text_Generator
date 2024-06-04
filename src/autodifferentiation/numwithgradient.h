#ifndef NUMWITHGRADIENT_H
#define NUMWITHGRADIENT_H

#include <vector>
#include "inum.h"

using namespace std;

class NumWithGradient : INum
{
private:
    double num_;
    double gradient_;
    vector<NumWithGradient *> depends_on;
    QString creation_op;

private:
    ///
    /// \brief ensureNum вспомогательный метод для
    /// превращения любого числа на входе в число
    /// с градиентом и его возвращение
    /// \param num - пришедшее абстрактное число
    /// с градиентом или без
    NumWithGradient *ensureNum(INum *num);

public:
    explicit NumWithGradient(double num,
                             vector<NumWithGradient *> depends_on
                                = vector<NumWithGradient *>{},
                             QString creation_op = "");

public:
    NumWithGradient operator+(INum *other);
    NumWithGradient operator*(INum *other);
    void backward(double backwardGradient = 0);
    double gradient();

    // Num interface
    double num() const override;
    Num_Type type() const override;
};

#endif // NUMWITHGRADIENT_H
