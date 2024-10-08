#ifndef LSTMMODEL_H
#define LSTMMODEL_H

#include "ineuralnetworkmodel.h"
#include "lstmlayer.h"

///
/// \brief The LSTMModel class
/// модель нейронной сети типа LSTM
class LSTMModel : public INeuralNetworkModel
{
private:
    QString _name; // для идентификации при сохранении/загрузке
    ILoss *_loss; // интерфейс вычисления потерь
    ITextEmbedding *_embedding; // интерфейс эмбеддинга
    QList<INeuralNetworkLayer *> _layers; // список слоев модели    

public:
    LSTMModel(QString name,
              ILoss *loss,
              ITextEmbedding *embedding,
              QList<INeuralNetworkLayer *> layers);
    LSTMModel(const QString path, const QString modelName, ILoss *loss);
    ~LSTMModel();

    // суффиксы именований файлов с данными о модели
    static QString LAYERS_DATA_NAME;
    static QString EMBEDDING_DATA_NAME;

    bool operator==(const LSTMModel model);

public:
    // INeuralNetworkModel interface
    void save(const QString path = QDir::currentPath(),
              bool inNewFolder = true) override;
    void load(const QString path = QDir::currentPath()) override;
    void drop() override;
    QString name() const override;
    int power() const override;
    ITextEmbedding *embedding() const override;
    QList<INeuralNetworkLayer *> layers() const override;
    Matrix3d<double> forward(Matrix3d<double> batch) override;
    Matrix3d<double> backward(Matrix3d<double> gradient) override;
    double singleStep(Matrix3d<double> xBatch,
                      Matrix3d<double> yBatch) override;
    //

};

#endif // LSTMMODEL_H
