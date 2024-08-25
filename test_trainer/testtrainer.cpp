#include <QObject>
#include <QtTest/QtTest>

#include "sgd.h"
#include "adagrad.h"
#include "lstmlayer.h"
#include "lstmmodel.h"
#include "softmaxcrossentropyloss.h"
#include "consistenttrainer.h"
#include "charasvectorembedding.h"

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
    ///
    /// \brief testConsistentTrainerSaveLoad
    /// тестирование корректности сохранения и загрузки
    /// данных обучения модели нейронной сети
    void testConsistentTrainerSaveLoad();
    ///
    /// \brief testConsistentTrainerSaveLoadVersionTwo
    /// тестирование корректности сохранения и загрузки
    /// данных обучения модели нейронной сети - версия два
    void testConsistentTrainerSaveLoadVersionTwo();
};

void TestTrainer::testConsistentTrainerOne()
{
    // инициализация
    int hiddenSize = 72;
    int batchSize = 22;
    int sequenceLenght = 44;
    try {
        CharAsVectorEmbedding *embedding
            = new CharAsVectorEmbedding("The_Body_Snatcher.txt",
                                        sequenceLenght, batchSize);
        LSTMModel model("LSTMModel",
                        new SoftmaxCrossEntropyLoss(), embedding,
                        QList<INeuralNetworkLayer *>{
                                new LSTMLayer("layer1", hiddenSize, 29),
                            });
        ConsistentTrainer trainer(&model, nullptr);
        trainer.refreshOptimizerStatus(new SGD(&model, 0.0055));
        // расчеты
        trainer.applyAssignmentForTrain(17, false, 5);
        trainer.train();
    } catch (const MatrixException &e) {
        cout << e.what();
    } catch (const NeuralNetworkException &e) {
        cout << e.what();
    } catch (const exception &e) {
        cout << e.what();
    }
}

void TestTrainer::testConsistentTrainerSaveLoad()
{
    // инициализация
    int hiddenSize = 64;
    int batchSize = 28;
    int sequenceLenght = 25;
    try {
        CharAsVectorEmbedding embedding("The_Body_Snatcher.txt", sequenceLenght, batchSize);
        LSTMLayer layer("layer1", hiddenSize, embedding.vocabSize());
        QList<INeuralNetworkLayer *> layers;
        layers.push_back(&layer);
        LSTMModel model("LSTMModelTestTwo", new SoftmaxCrossEntropyLoss(), &embedding, layers);
        SGD *optimizer = new SGD(&model, 0.004, true);
        ConsistentTrainer trainer(&model, optimizer);
        // расчеты
        trainer.applyAssignmentForTrain(16, false, 5);
        trainer.train();
        trainer.save();
        ConsistentTrainer properTrainer(&model, nullptr);
        properTrainer.load(QDir::currentPath());

        QCOMPARE(trainer == properTrainer, true);
        optimizer->newLearningRate(0.01);
        QCOMPARE(trainer == properTrainer, false);
    } catch (const MatrixException &e) {
        cout << e.what();
    } catch (const NeuralNetworkException &e) {
        cout << e.what();
    } catch (const exception &e) {
        cout << e.what();
    }
}

void TestTrainer::testConsistentTrainerSaveLoadVersionTwo()
{
    // инициализация
    int hiddenSize = 100;
    int batchSize = 44;
    int sequenceLenght = 32;
    try {
        CharAsVectorEmbedding embedding("The_Body_Snatcher.txt", sequenceLenght, batchSize);
        LSTMLayer layer("layer1", hiddenSize, embedding.vocabSize());
        QList<INeuralNetworkLayer *> layers;
        layers.push_back(&layer);
        LSTMModel model("LSTMModelTestTwoVersionTwo", new SoftmaxCrossEntropyLoss(), &embedding, layers);
        AdaGrad *optimizer = new AdaGrad(&model, 0.00077, true);
        ConsistentTrainer trainer(&model, optimizer);
        // расчеты
        trainer.applyAssignmentForTrain(7, false, 3);
        trainer.train();
        trainer.save();
        ConsistentTrainer properTrainer(&model, nullptr);
        properTrainer.load(QDir::currentPath());

        QCOMPARE(trainer == properTrainer, true);
        optimizer->newLearningRate(0.002);
        QCOMPARE(trainer == properTrainer, false);
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
