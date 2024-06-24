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
    Matrix3d<double> sequenceOut = layer.forward(sequenceIn);
    sequenceOut.print();

    QCOMPARE(sequenceIn == sequenceOut, false);
}

QTEST_MAIN(TestNeuralNetwork)
#include "testneuralnetwork.moc"
