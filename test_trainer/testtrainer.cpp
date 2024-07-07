#include <QObject>
#include <QtTest/QtTest>

#include "sgd.h"
#include "adagrad.h"
#include "lstmlayer.h"
#include "lstmmodel.h"
#include "softmaxcrossentropyloss.h"
#include "consistenttrainer.h"
#include "charasvectorembedding.h"
#include "charasvectorembedding.cpp"

using namespace std;

class TestTrainer: public QObject
{
    Q_OBJECT

private slots:
    ///
    /// \brief testConsistentTrainerOne
    /// тестирование работоспособности последовательного
    /// тестера для нейронной сети - вариант 1
    void testConsistentTrainerOne();
};

void TestTrainer::testConsistentTrainerOne()
{
    // инициализация
    int hiddenSize = 256;
    int batchSize = 64;
    int sequenceLenght = 32;
    CharAsVectorEmbedding<double> embedding("The_Body_Snatcher.txt", sequenceLenght, batchSize);
    LSTMLayer layer("layer1", hiddenSize, embedding.vocabSize());
    layer.loadParams(QDir::currentPath());
    QList<INeuralNetworkLayer *> layers;
    layers.push_back(&layer);
    LSTMModel model("LSTMModel", new SoftmaxCrossEntropyLoss(), layers);
    //AdaGrad optimizer(&model, 0.004);
    SGD optimizer(&model, 0.003, true);
    ConsistentTrainer trainer(&model, &embedding, &optimizer,
                              sequenceLenght, batchSize);
    // расчеты
    try {
        trainer.train(17, true, 5);
    } catch (const MatrixException &e) {
        cout << e.what();
    } catch (const NeuralNetworkException &e) {
        cout << e.what();
    } catch (const exception &e) {
        cout << e.what();
    }
}

QTEST_MAIN(TestTrainer)
#include "testtrainer.moc"
