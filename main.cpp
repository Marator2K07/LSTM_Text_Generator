#include <QApplication>

#include "pageModels/pagemodel.h"
#include "adagrad.h"
#include "sgd.h"
#include "lstmlayer.h"
#include "lstmmodel.h"
#include "softmaxcrossentropyloss.h"
#include "consistenttrainer.h"
#include "charasvectorembedding.h"
#include "charasvectorembedding.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 128_54_33(88_44_26)
    // 256_32_25(два слоя)(The_Body_Snatcher)
    // 128_22_44(два слоя)(The_Body_Snatcher)
    // 160_24_48(один слой)(TheRedRoom)

    // инициализация
    int hiddenSize = 128;
    int batchSize = 33;
    int sequenceLenght = 33;
    CharAsVectorEmbedding<double> embedding("LearningDataOne.txt", sequenceLenght, batchSize);
    //LSTMLayer layer1("222_33_55_Layer1", hiddenSize, embedding.vocabSize(), 0.1);
    //LSTMLayer layer2("222_33_55_Layer2", hiddenSize, embedding.vocabSize(), 0.01);
    //LSTMLayer layer1("128_54_33_Layer1", hiddenSize, embedding.vocabSize(), 0.1);
    //LSTMLayer layer2("128_54_33_Layer2", hiddenSize, embedding.vocabSize(), 0.01);
    LSTMLayer layer1("128_33_33_Layer1", hiddenSize, embedding.vocabSize(), 0.01);
    //LSTMLayer layer2("128_24_50_Layer2", hiddenSize, embedding.vocabSize(), 0.001);
    cout << embedding.vocabSize() << endl;
    layer1.loadParams(QDir::currentPath());
    //layer2.loadParams(QDir::currentPath());
    QList<INeuralNetworkLayer *> layers;
    layers.push_back(&layer1);
    //layers.push_back(&layer2);
    LSTMModel model(new SoftmaxCrossEntropyLoss(), layers);
    SGD optimizer(&model, 0.0033, true);
    // AdaGrad optimizer(&model, 0.0004);
    ConsistentTrainer trainer(&model, &embedding, &optimizer,
                              sequenceLenght, batchSize);
    // расчеты
    try {
        trainer.train(345, false, 200);
        //trainer.sampleOutput('u', '.');
    } catch (const MatrixException &e) {
        cout << e.what();
    } catch (const NeuralNetworkException &e) {
        cout << e.what();
    } catch (const exception &e) {
        cout << e.what();
    }

    return a.exec();
}
