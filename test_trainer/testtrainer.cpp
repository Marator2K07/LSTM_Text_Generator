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
    int hiddenSize = 128;
    int batchSize = 16;
    int sequenceLenght = 12;
    CharAsVectorEmbedding<double> embedding("Plain_Kate.txt", sequenceLenght, batchSize);
    LSTMModel model(new SoftmaxCrossEntropyLoss(),
                        QList<INeuralNetworkLayer *>{
                            new LSTMLayer(hiddenSize, embedding.vocabSize())
                        });
    AdaGrad optimizer(&model, 0.005, true);
    //SGD optimizer(&model, 0.005, true);
    ConsistentTrainer trainer(&model, &embedding, &optimizer,
                              sequenceLenght, batchSize);
    // расчеты
    try {
        trainer.train(222, true, 25);
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
