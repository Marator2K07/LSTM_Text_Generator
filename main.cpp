#include <QCoreApplication>

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
    QCoreApplication a(argc, argv);

    // инициализация
    int hiddenSize = 77;
    int batchSize = 16;
    int sequenceLenght = 12;
    CharAsVectorEmbedding<double> embedding("Plain_Kate.txt", sequenceLenght, batchSize);
    LSTMModel model(new SoftmaxCrossEntropyLoss(),
                    QList<INeuralNetworkLayer *>{
                        new LSTMLayer(hiddenSize, embedding.vocabSize())
                    });
    SGD optimizer(&model, 0.007, true);
    ConsistentTrainer trainer(&model, &embedding, &optimizer,
                              sequenceLenght, batchSize);
    // расчеты
    try {
        trainer.train(500, true, 25);
    } catch (const MatrixException &e) {
        cout << e.what();
    } catch (const NeuralNetworkException &e) {
        cout << e.what();
    } catch (const exception &e) {
        cout << e.what();
    }

    return a.exec();
}
