#include <QObject>
#include <QtTest/QtTest>
#include <QMapIterator>

#include "lstmnode.h"
#include "lstmlayer.h"

using namespace std;

class TestNeuralNetwork: public QObject
{
    Q_OBJECT

private slots:
    ///
    /// \brief testLSTMLayerForward
    /// поверхностная проверка работоспособности прямого прохода слоя LSTM
    void testLSTMLayerForward();
    ///
    /// \brief testLSTMLayerBackward
    /// поверхностная проверка работоспособности обратного прохода слоя LSTM
    void testLSTMLayerBackward();
};

void TestNeuralNetwork::testLSTMLayerForward()
{
    // инициализация
    int batchSize = 44;
    int outputSize = 33;
    int sequenceLenght = 8;
    int vocabSize = 28;
    LSTMLayer layer(batchSize, outputSize);
    Matrix3d<double> sequenceIn
        = Matrix3d<double>::zeroM(batchSize, sequenceLenght, vocabSize);
    // расчеты
    try {
        Matrix3d<double> sequenceOut = layer.forward(sequenceIn);
        //sequenceOut.print();

        QCOMPARE(sequenceIn == sequenceOut, false);
    } catch (const NeuralNetworkException &e) {
        cout << e.what() << endl;
    }
}

void TestNeuralNetwork::testLSTMLayerBackward()
{
    // инициализация
    int batchSize = 64;
    int outputSize = 44;
    int sequenceLenght = 10;
    int vocabSize = 44;
    LSTMLayer layer(batchSize, outputSize);
    Matrix3d<double> sequenceIn
        = Matrix3d<double>::zeroM(batchSize, sequenceLenght, vocabSize);
    Matrix3d<double> gradOut
        = Matrix3d<double>::randomNormal(0.0, 0.01,
                                         batchSize, sequenceLenght, vocabSize);
    // расчеты
    try {
        Matrix3d<double> sequenceOut = layer.forward(sequenceIn);
        Matrix3d<double> gradIn = layer.backward(gradOut);
        gradIn.print();

        QCOMPARE(gradOut == gradIn, false);
    } catch (const NeuralNetworkException &e) {
        cout << e.what() << endl;
    }
}

QTEST_MAIN(TestNeuralNetwork)
#include "testneuralnetwork.moc"
