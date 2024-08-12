#ifndef LSTMNODE_H
#define LSTMNODE_H

#include "ineuralnetworknode.h"

///
/// \brief The LSTMNode class
/// узла нейронной сети типа LSTM
class LSTMNode : public INeuralNetworkNode
{
private:
    // данные прямого прохода LSTM узла нейронной сети
    IMatrix<double> *_xIn;
    IMatrix<double> *_cIn;
    IMatrix<double> *_z;
    IMatrix<double> *_fInter;
    IMatrix<double> *_f;
    IMatrix<double> *_iInter;
    IMatrix<double> *_i;
    IMatrix<double> *_cBarInter;
    IMatrix<double> *_cBar;
    IMatrix<double> *_oInter;
    IMatrix<double> *_o;
    IMatrix<double> *_cOut;
    IMatrix<double> *_hOut;
    IMatrix<double> *_xOut;
    //

private:
    ///
    /// \brief cleanUp подчистка памяти после прямого
    /// и обратного проходов по заданным параметрам слоя
    void cleanUp();

public:
    LSTMNode();
    ~LSTMNode();

public:
    // INeuralNetworkNode interface
    QMap<QString, Matrix2d<double>>
    forward(Matrix2d<double> xIn,
            Matrix2d<double> hIn,
            Matrix2d<double> cIn,
            QMap<QString, QMap<QString, Matrix2d<double>>> &layerParams) override;
    QMap<QString, Matrix2d<double>>
    backward(Matrix2d<double> xOutGrad,
             Matrix2d<double> hOutGrad,
             Matrix2d<double> cOutGrad,
             QMap<QString, QMap<QString, Matrix2d<double>>> &layerParams) override;
    //

};

#endif // LSTMNODE_H
