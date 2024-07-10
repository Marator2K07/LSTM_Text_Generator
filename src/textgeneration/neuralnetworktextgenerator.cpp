#include "neuralnetworktextgenerator.h"

NeuralNetworkTextGenerator::NeuralNetworkTextGenerator(INeuralNetworkModel neuralNetworkModel,
                                                       QObject *parent)
    : _neuralNetworkModel{neuralNetworkModel}
    , QObject{parent}
{

}

INeuralNetworkModel *NeuralNetworkTextGenerator::neuralNetworkModel() const
{
    return _neuralNetworkModel;
}

}
