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
