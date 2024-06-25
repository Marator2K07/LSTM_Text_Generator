#include "sgd.h"

SGD::SGD(INeuralNetworkModel *model,
         double learningRate,
         bool gradientClip)
    : _model{model}
    , _learningRate{learningRate}
    , _gradientClip{gradientClip}
{
}

void SGD::update()
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

{

}
