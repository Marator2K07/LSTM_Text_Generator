#include <QObject>
#include <QtTest/QtTest>

#include "sgd.h"
#include "adagrad.h"
#include "lstmmodel.h"
#include "lstmlayer.h"
#include "softmaxcrossentropyloss.h"
#include "charasvectorembedding.h"

using namespace std;

class TestOptimizer: public QObject
{
    Q_OBJECT

private slots:
    ///
    /// \brief testSGDOptimizer
    /// тестирование работоспособности SGD
    /// оптимизатора для нейронной сети
    void testSGDOptimizer();
    ///
    /// \brief testAdaGradOptimizer
    /// тестирование работоспособности AdaGrad
    /// оптимизатора для нейронной сети
    void testAdaGradOptimizer();
};

void TestOptimizer::testSGDOptimizer()
{
    // инициализация
    int hiddenSize = 111;
    int batchSize = 12;
    int sequenceLenght = 22;
    CharAsVectorEmbedding *txtEmbed
        = new CharAsVectorEmbedding("Plain_Kate.txt", sequenceLenght, batchSize);
    LSTMModel lstmModel("LSTMModelSGD",
                        new SoftmaxCrossEntropyLoss(),
                        txtEmbed,
                        QList<INeuralNetworkLayer *>{
                            new LSTMLayer("layer1", hiddenSize, txtEmbed->vocabSize())
                        });
    SGD SGDOptimizer(&lstmModel, 0.008, true);
    // расчеты
    try {
        Matrix2d<double> indicesPred = txtEmbed->genTextIndices(0);
        Matrix3d<double> batchPred = txtEmbed->genTextBatch(indicesPred);
        Matrix2d<double> indicesTarget = txtEmbed->genTextIndices(1);
        Matrix3d<double> batchTarget = txtEmbed->genTextBatch(indicesTarget);

        for (int i = 0; i < 3; ++i) {
            double resLossAfterFirstStep
                = lstmModel.singleStep(batchPred, batchTarget);
            cout << i << "): " << resLossAfterFirstStep << endl;
            SGDOptimizer.update();

            double resLossAfterSecondStep
                = lstmModel.singleStep(batchPred, batchTarget);
            cout << i << "): " << resLossAfterSecondStep << endl;
            SGDOptimizer.update();

            QCOMPARE(resLossAfterFirstStep > resLossAfterSecondStep, true);
        }
    } catch (const MatrixException &e) {
        cout << e.what();
    } catch (const NeuralNetworkException &e) {
        cout << e.what();
    } catch (const exception &e) {
        cout << e.what();
    }
}

void TestOptimizer::testAdaGradOptimizer()
{
    // инициализация
    int hiddenSize = 128;
    int batchSize = 16;
    int sequenceLenght = 12;
    CharAsVectorEmbedding *txtEmbed
        = new CharAsVectorEmbedding("Plain_Kate.txt", sequenceLenght, batchSize);
    LSTMModel lstmModel("LSTMModelAdaGrad",
                        new SoftmaxCrossEntropyLoss(),
                        txtEmbed,
                        QList<INeuralNetworkLayer *>{
                            new LSTMLayer("layer1", hiddenSize, txtEmbed->vocabSize(), 0.01)
                        });
    AdaGrad AdaGradOptimizer(&lstmModel, 0.005);
    // расчеты
    try {
        Matrix2d<double> indicesPred = txtEmbed->genTextIndices(0);
        Matrix3d<double> batchPred = txtEmbed->genTextBatch(indicesPred);
        Matrix2d<double> indicesTarget = txtEmbed->genTextIndices(1);
        Matrix3d<double> batchTarget = txtEmbed->genTextBatch(indicesTarget);

        for (int i = 0; i < 3; ++i) {
            double resLossAfterFirstStep
                = lstmModel.singleStep(batchPred, batchTarget);
            cout << i << "): " << resLossAfterFirstStep << endl;
            AdaGradOptimizer.update();

            double resLossAfterSecondStep
                = lstmModel.singleStep(batchPred, batchTarget);
            cout << i << "): " << resLossAfterSecondStep << endl;
            AdaGradOptimizer.update();

            QCOMPARE(resLossAfterFirstStep > resLossAfterSecondStep, true);
        }
    } catch (const MatrixException &e) {
        cout << e.what();
    } catch (const NeuralNetworkException &e) {
        cout << e.what();
    } catch (const exception &e) {
        cout << e.what();
    }
}

QTEST_MAIN(TestOptimizer)
#include "testoptimizer.moc"
