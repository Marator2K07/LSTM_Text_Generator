#include "distributor.h"

Distributor *Distributor::_distributor = nullptr;

Distributor::Distributor()
{
}

Distributor *Distributor::instance()
{
    // если главное поле не проинициализировано,
    // то инициализируем его в первый и последний раз
    if (_distributor == nullptr) {
        _distributor = new Distributor();
    }

    return _distributor;
}

double Distributor::normal(double mean, double width)
{
    // задаем все необходимые параметры генерации
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> distribution(mean, width);

    return distribution(gen);
}

int Distributor::discrete(vector<double> weightVector)
{
    // задаем все необходимые параметры генерации
    random_device rd;
    mt19937 gen(rd());
    discrete_distribution<> distribution(weightVector.begin(),
                                         weightVector.end());

    return distribution(gen);
}
