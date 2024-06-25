#include "sgd.h"

SGD::SGD(double learningRate, bool gradientClip)
    : _learningRate{learningRate}
    , _gradientClip{gradientClip}
{
}

void SGD::updateRule(QMap<QString, Matrix2d<double>> &stepParams)
{
    // получаем обновленное значение градиента
    Matrix2d<double> updateGrad(
        stepParams.value("grad").multiplication(_learningRate)->data()
        );
    // обновляем параметр сети
    stepParams.insert(
        "param",
        Matrix2d<double>(
            stepParams["param"].subtraction(&updateGrad)->data()
            )
        );
}

void SGD::step()
{

}
