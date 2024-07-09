#ifndef LSTMMODEL_H
#define LSTMMODEL_H

#include "ineuralnetworkmodel.h"
#include "itextembedding.h"
#include "lstmlayer.h"

///
/// \brief The LSTMModel class
/// модель нейронной сети типа LSTM
class LSTMModel : public INeuralNetworkModel
{
private:
    QString _name; // для идентификации при сохранении/загрузке
    ILoss *_loss; // интерфейс вычисления потерь
    ITextEmbedding<double> *_embedding; // интерфейс эмбеддинга
    QList<INeuralNetworkLayer *> _layers; // список слоев модели
    const QString LAYERS_DATA_NAME = "layersData";
    const QString EMBEDDING_DATA_NAME = "embeddingData";

public:
    LSTMModel(QString name,
              ILoss *loss,
              ITextEmbedding<double> *embedding,
              QList<INeuralNetworkLayer *> layers);
    LSTMModel(const QString path, const QString modelName, ILoss *loss);

    bool operator==(const LSTMModel model);

public:
    // INeuralNetworkModel interface
    void save(const QString path = QDir::currentPath()) override;
    void load(const QString path = QDir::currentPath()) override;
    QList<INeuralNetworkLayer *> layers() const override;
    Matrix3d<double> forward(Matrix3d<double> batch) override;
    Matrix3d<double> backward(Matrix3d<double> gradient) override;
    double singleStep(Matrix3d<double> xBatch,
                      Matrix3d<double> yBatch) override;
    //

};

#endif // LSTMMODEL_H
