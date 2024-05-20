#ifndef NUMWITHGRADIENT_H
#define NUMWITHGRADIENT_H

#include <QString>
#include <vector>

using namespace std;

class NumWithGradient
{
private:
    double num_;
    double gradient;
    vector<double> depends_on;
    QString creation_op;

public:
    explicit NumWithGradient(double num);

public:

};

#endif // NUMWITHGRADIENT_H
