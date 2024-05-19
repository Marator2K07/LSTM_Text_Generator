#ifndef NUMWITHGRADIENT_H
#define NUMWITHGRADIENT_H

#include <QString>
#include <QVariant>
#include <vector>

using namespace std;

class NumWithGradient
{
private:
    QVariant num;
    QVariant gradient;
    vector<double> depends_on;
    QString creation_op;

public:
    explicit NumWithGradient(QVariant num);

public:

};

#endif // NUMWITHGRADIENT_H
