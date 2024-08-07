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
    int hiddenSize = 128;
    int batchSize = 32;
    int sequenceLenght = 33;
    try {
        CharAsVectorEmbedding<double> embedding("The_Body_Snatcher.txt", sequenceLenght, batchSize);
        LSTMLayer layer("layer1", hiddenSize, embedding.vocabSize());
        layer.loadParams(QDir::currentPath());
        QList<INeuralNetworkLayer *> layers;
        layers.push_back(&layer);
        LSTMModel model("LSTMModel", new SoftmaxCrossEntropyLoss(), &embedding, layers);
        //AdaGrad optimizer(&model, 0.004);
        SGD optimizer(&model, 0.003, true);
        ConsistentTrainer trainer(&model, &optimizer);
        // расчеты
        trainer.applyAssignmentForTrain(17, true, 5);
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
        CharAsVectorEmbedding<double> embedding("The_Body_Snatcher.txt", sequenceLenght, batchSize);
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
        ConsistentTrainer properTrainer(QDir::currentPath(), &model);

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
        CharAsVectorEmbedding<double> embedding("The_Body_Snatcher.txt", sequenceLenght, batchSize);
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
        ConsistentTrainer properTrainer(QDir::currentPath(), &model);

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
