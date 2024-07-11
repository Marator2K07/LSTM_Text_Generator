#include <QObject>
#include <QtTest/QtTest>
#include <QMapIterator>

#include "softmaxcrossentropyloss.h"
#include "charasvectorembedding.cpp"
#include "lstmnode.h"
#include "lstmlayer.h"
#include "lstmmodel.h"

using namespace std;

class TestNeuralNetwork: public QObject
{
    Q_OBJECT

private slots:
    ///
    /// \brief testLSTMnode
    /// простая проверка работоспособности узла типа LSTM вручную
    void testLSTMnode();
    ///
    /// \brief testLSTMLayerForward
    /// поверхностная проверка работоспособности прямого прохода слоя LSTM
    void testLSTMLayerForward();
    ///
    /// \brief testLSTMLayerBackward
    /// поверхностная проверка работоспособности обратного прохода слоя LSTM
    void testLSTMLayerBackward();
    ///
    /// \brief testSaveLoadLSTMLayer
    /// проверка работоспособности сохранения и загрузки параметров слоя LSTM
    void testSaveLoadLSTMLayer();
    ///
    /// \brief testLSTMModelOne
    /// первый тест модели нейронной сети типа LSTM
    void testLSTMModelOne();
    ///
    /// \brief testLSTMModelSaveLoad
    /// проверка работоспособности сохранения и загрузки модели LSTM
    void testLSTMModelSaveLoad();
};

void TestNeuralNetwork::testLSTMnode()
{
    // инициализация
    int hiddenSize = 12;
    int batchSize = 6;
    int outputSize = 4;
    int vocabSize = 4;
    LSTMNode node;
    QMap<QString, QMap<QString, Matrix2d<double>>> layerParams;
    layerParams.insert("W_f", QMap<QString, Matrix2d<double>>());
    layerParams.insert("B_f", QMap<QString, Matrix2d<double>>());
    layerParams.insert("W_i", QMap<QString, Matrix2d<double>>());
    layerParams.insert("B_i", QMap<QString, Matrix2d<double>>());
    layerParams.insert("W_c", QMap<QString, Matrix2d<double>>());
    layerParams.insert("B_c", QMap<QString, Matrix2d<double>>());
    layerParams.insert("W_o", QMap<QString, Matrix2d<double>>());
    layerParams.insert("B_o", QMap<QString, Matrix2d<double>>());
    layerParams.insert("W_v", QMap<QString, Matrix2d<double>>());
    layerParams.insert("B_v", QMap<QString, Matrix2d<double>>());
    layerParams["W_f"].insert(
        "value",
        Matrix2d<double>::randomNormal(0.0, 0.01, hiddenSize+vocabSize, hiddenSize)
        );
    layerParams["B_f"].insert(
        "value",
        Matrix2d<double>::randomNormal(0.0, 0.01, 1, hiddenSize)
        );
    layerParams["W_i"].insert(
        "value",
        Matrix2d<double>::randomNormal(0.0, 0.01, hiddenSize+vocabSize, hiddenSize));
    layerParams["B_i"].insert(
        "value",
        Matrix2d<double>::randomNormal(0.0, 0.01, 1, hiddenSize)
        );
    layerParams["W_c"].insert(
        "value",
        Matrix2d<double>::randomNormal(0.0, 0.01, hiddenSize+vocabSize, hiddenSize));
    layerParams["B_c"].insert(
        "value",
        Matrix2d<double>::randomNormal(0.0, 0.01, 1, hiddenSize)
        );
    layerParams["W_o"].insert(
        "value",
        Matrix2d<double>::randomNormal(0.0, 0.01, hiddenSize+vocabSize, hiddenSize));
    layerParams["B_o"].insert(
        "value",
        Matrix2d<double>::randomNormal(0.0, 0.01, 1, hiddenSize)
        );
    layerParams["W_v"].insert(
        "value",
        Matrix2d<double>::randomNormal(0.0, 0.01, hiddenSize, outputSize));
    layerParams["B_v"].insert(
        "value",
        Matrix2d<double>::randomNormal(0.0, 0.01, 1, outputSize)
        );

    const QList<QString> keys = layerParams.keys();
    for (const QString &key : keys) {
        layerParams[key].insert(
            "deriv",
            Matrix2d<double>::zeroM(
                layerParams[key]["value"].sizes()[0],
                layerParams[key]["value"].sizes()[1])
            );
    }

    try {
    QMap<QString, Matrix2d<double>> forwardMap
        = node.forward(Matrix2d<double>::zeroM(batchSize, vocabSize),
                       Matrix2d<double>::zeroM(batchSize, hiddenSize),
                       Matrix2d<double>::zeroM(batchSize, hiddenSize),
                       layerParams);
    //forwardMap["X_out"].print();
    //forwardMap["H_out"].print();
    //forwardMap["C_out"].print();

    vector<unsigned long long> properXoutSizes{batchSize, outputSize};
    vector<unsigned long long> properHoutSizes{batchSize, hiddenSize};
    vector<unsigned long long> properCoutSizes{batchSize, hiddenSize};
    QCOMPARE(forwardMap["X_out"].sizes(), properXoutSizes);
    QCOMPARE(forwardMap["H_out"].sizes(), properHoutSizes);
    QCOMPARE(forwardMap["C_out"].sizes(), properCoutSizes);

    //QMap<QString, Matrix2d<double>> backwardMap
    //    = node.backward(Matrix2d<double>::zeroM(1, vocabSize),
    //                    Matrix2d<double>::zeroM(1, hiddenSize),
    //                    Matrix2d<double>::zeroM(1, hiddenSize),
    //                    layerParams);
    //forwardMap["dX_prev"].print();
    //forwardMap["dH_prev"].print();
    //forwardMap["dC_prev"].print();
    } catch (const NeuralNetworkException &e) {
        cout << e.what() << endl;
    }
}

void TestNeuralNetwork::testLSTMLayerForward()
{
    try {
        // инициализация
        int hiddenSize = 128;
        int outputSize = 44;
        LSTMLayer layer("layer1", hiddenSize, outputSize);
        int batchSize = 64;
        int sequenceLenght = 10;
        int vocabSize = 44;
        Matrix3d<double> sequenceIn
            = Matrix3d<double>::zeroM(batchSize, sequenceLenght, vocabSize);
        // расчеты
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
    try {
        int hiddenSize = 128;
        int outputSize = 44;
        LSTMLayer layer("layer1", hiddenSize, outputSize);
        int batchSize = 64;
        int sequenceLenght = 10;
        int vocabSize = 44;
        Matrix3d<double> sequenceIn
            = Matrix3d<double>::zeroM(batchSize, sequenceLenght, vocabSize);
        Matrix3d<double> gradOut
            = Matrix3d<double>::randomNormal(0.0, 0.01,
                                             batchSize, sequenceLenght, vocabSize);
        // расчеты
        Matrix3d<double> sequenceOut = layer.forward(sequenceIn);
        Matrix3d<double> gradIn = layer.backward(gradOut);
        //gradIn.print();

        QCOMPARE(gradOut == gradIn, false);
    } catch (const NeuralNetworkException &e) {
        cout << e.what() << endl;
    }
}

void TestNeuralNetwork::testSaveLoadLSTMLayer()
{
    // инициализация
    int hiddenSize = 128;
    int batchSize = 32;
    int sequenceLenght = 22;
    int outputSize = 11;
    int vocabSize = 11;
    LSTMLayer layer("LayerTest", hiddenSize, outputSize);
    Matrix3d<double> sequenceIn
        = Matrix3d<double>::randomNormal(0.0, 0.01,
                                         batchSize, sequenceLenght, vocabSize);
    Matrix3d<double> gradOut
        = Matrix3d<double>::randomNormal(0.0, 0.01,
                                         batchSize, sequenceLenght, vocabSize);
    // расчеты
    try {
        Matrix3d<double> sequenceOut = layer.forward(sequenceIn);
        Matrix3d<double> gradIn = layer.backward(gradOut);
        layer.saveParams();
        LSTMLayer properLayer(QDir::currentPath(), "LayerTest");

        QCOMPARE(layer.compareLayer(&properLayer), true);
    } catch (const NeuralNetworkException &e) {
        cout << e.what() << endl;
    } catch (const exception &e) {
        cout << e.what() << endl;
    }
}

void TestNeuralNetwork::testLSTMModelOne()
{
    // инициализация
    int hiddenSize = 128;
    int batchSize = 64;
    int sequenceLenght = 10;
    int outputSize = 44;
    int vocabSize = 44;
    CharAsVectorEmbedding<double> embedding("test_text.txt", sequenceLenght, batchSize);
    LSTMModel lstmModel("testLSTMModel",
                        new SoftmaxCrossEntropyLoss(),
                        &embedding,
                        QList<INeuralNetworkLayer *>{
                            new LSTMLayer("layer1", hiddenSize, outputSize)
                        });
    // расчеты
    double resLossAfter1Step
        = lstmModel.singleStep(Matrix3d<double>::zeroM(batchSize, sequenceLenght, vocabSize),
                               Matrix3d<double>::zeroM(batchSize, sequenceLenght, vocabSize));
    double resLossAfter2Step
        = lstmModel.singleStep(Matrix3d<double>::randomNormal(0.0, 0.01,
                                                              batchSize, sequenceLenght, vocabSize),
                               Matrix3d<double>::randomNormal(0.0, 0.01,
                                                              batchSize, sequenceLenght, vocabSize));
    cout << resLossAfter1Step << endl << resLossAfter2Step << endl;

    QCOMPARE(resLossAfter1Step != resLossAfter2Step, true);
}

void TestNeuralNetwork::testLSTMModelSaveLoad()
{
    // инициализация
    int hiddenSize = 77;
    int batchSize = 44;
    int sequenceLenght = 33;
    int outputSize = 22;
    int vocabSize = 22;
    LSTMLayer layer1("layer1", hiddenSize*2, vocabSize);
    LSTMLayer layer2("layer2", hiddenSize, vocabSize);
    QList<INeuralNetworkLayer *> layers;
    layers.push_back(&layer1);
    layers.push_back(&layer2);
    CharAsVectorEmbedding<double> embedding("test_text.txt", sequenceLenght, batchSize);
    LSTMModel lstmModel("testLSTMModel", new SoftmaxCrossEntropyLoss(), &embedding, layers);
    // расчеты
    try {
        lstmModel.singleStep(Matrix3d<double>::zeroM(batchSize, sequenceLenght, vocabSize),
                             Matrix3d<double>::randomNormal(0.0, 0.01,
                                                            batchSize, sequenceLenght, vocabSize));
        lstmModel.save();
        LSTMModel properLstmModel(QDir::currentPath(), "testLSTMModel", new SoftmaxCrossEntropyLoss());

        QCOMPARE(lstmModel == properLstmModel, true);
    } catch (const NeuralNetworkException &e) {
        cout << e.what() << endl;
    } catch (const MatrixException &e) {
        cout << e.what() << endl;
    } catch (const exception &e) {
        cout << e.what() << endl;
    }

}

QTEST_MAIN(TestNeuralNetwork)
#include "testneuralnetwork.moc"
