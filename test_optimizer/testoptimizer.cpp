#include <QObject>
#include <QtTest/QtTest>

#include "sgd.h"
#include "lstmmodel.h"
#include "lstmlayer.h"
#include "softmaxcrossentropyloss.h"
#include "charasvectorembedding.h"
#include "charasvectorembedding.cpp"

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
};

void TestOptimizer::testSGDOptimizer()
{
    // инициализация
    int hiddenSize = 128;
    int batchSize = 32;
    int sequenceLenght = 10;
    CharAsVectorEmbedding<double> txtEmbed("Plain_Kate.txt", sequenceLenght, batchSize);
    LSTMModel lstmModel(new SoftmaxCrossEntropyLoss(),
                        QList<INeuralNetworkLayer *>{
                            new LSTMLayer(hiddenSize, txtEmbed.vocabSize())
                        });
    SGD SGDOptimizer(&lstmModel, 0.001, true);
    // расчеты
    try {
        Matrix2d<double> indicesPred = txtEmbed.genTextIndices(0);
        Matrix3d<double> batchPred = txtEmbed.genTextBanch(indicesPred);
        Matrix2d<double> indicesTarget = txtEmbed.genTextIndices(1);
        Matrix3d<double> batchTarget = txtEmbed.genTextBanch(indicesTarget);

        for (int i = 0; i < 3; ++i) {
            double resLossAfterFirstStep
                = lstmModel.singleStep(batchPred, batchTarget);
            cout << resLossAfterFirstStep << endl;
            SGDOptimizer.update();

            double resLossAfterSecondStep
                = lstmModel.singleStep(batchPred, batchTarget);
            cout << resLossAfterSecondStep << endl;
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

QTEST_MAIN(TestOptimizer)
#include "testoptimizer.moc"
