#include "distributor.h"

Distributor *Distributor::distributor = nullptr;

Distributor *Distributor::instance()
{
    // если поле не проинициализировано,
    // то инициализируем его впервый и последний раз
    if (distributor == nullptr) {
        distributor = new Distributor;
    }

    return distributor;
}
