#include "lstmnode.h"

LSTMNode::LSTMNode(int hiddenSize, int vocabSize)
    : _hiddenSize{hiddenSize}
    , _vocabSize{vocabSize}
{
}

QMap<QString, Matrix2d<double>>
LSTMNode::forward(QMap<QString, Matrix2d<double>> input,
                  QMap<QString, QMap<QString, Matrix2d<double>>> &layerParams)
{

}

QMap<QString, Matrix2d<double>>
LSTMNode::backward(QMap<QString, Matrix2d<double>> outputGrad,
                   QMap<QString, QMap<QString, Matrix2d<double>>> &layerParams)
{

}
