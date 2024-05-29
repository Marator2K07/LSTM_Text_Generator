#include "softmaxcrossentropyloss.h"

SoftmaxCrossEntropyLoss::SoftmaxCrossEntropyLoss()
{

}

double SoftmaxCrossEntropyLoss::forward(vector<vector<double>> prediction,
                                        vector<vector<double>> target)
{
    // проверки
    if (prediction.size() != target.size() ||
        prediction[0].size() != target.size()) {
        return 0.0;
    }
    // остальные операции...
    _prediction = prediction;
    _target = target;
    // возвращаем расчитанную потерю
    return calculate();
}

vector<vector<double> > SoftmaxCrossEntropyLoss::backward()
{

}

double SoftmaxCrossEntropyLoss::calculate()
{

}

vector<vector<double> > SoftmaxCrossEntropyLoss::inputGradient()
{

}
