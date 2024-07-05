#include "lstmmodel.h"
#include "matrix3d.cpp"

LSTMModel::LSTMModel(QString name,
                     ILoss *loss,
                     QList<INeuralNetworkLayer *> layers)
    : _name{name}
    , _loss{loss}
    , _layers{layers}
{
}

LSTMModel::LSTMModel(const QString path, const QString modelName)
    : _name{modelName}
{
    load(QString("%1/%2").arg(path, modelName));
}

bool LSTMModel::operator==(const LSTMModel model)
{
    // смотрим совпадает ли количество слоев в моделях
    if (_layers.size() != model.layers().size()) {
        return false;
    }
    // если все впорядке то сравниваем послойно
    for (int i = 0; i < _layers.size(); ++i) {
        bool equalStepLayer = _layers.at(i) == model.layers().at(i);
        if (!equalStepLayer) {
            return false;
        }
    }
    return true;
}

void LSTMModel::save(const QString path)
{
    // создаем новую папку в указанном месте
    QString folderPath = QString("%1/%2").arg(path, _name);
    QDir dir;
    dir.mkdir(folderPath);
    // пытаемся открыть файл для сохранения в новой папке
    QString fileName = QString("%1/%2.txt").arg(folderPath, _name);
    ofstream file;
    file.open(fileName.toStdString());
    if (!file.is_open()) {
        throw NeuralNetworkException(
            QString("Catch neural network model saving exception:\n[%1]\n")
                .arg("Failed to open file")
            );
    }
    // пишем информацию о слоях и одновременно пишем имена слоев в файл
    try {
        for (INeuralNetworkLayer *layer : _layers) {
            file << layer->name().toStdString() << endl;
            layer->saveParams(folderPath);
        }
    } catch (const NeuralNetworkException &e) {
        throw NeuralNetworkException(
            QString("Catch neural network model saving layers exception:\n[%1]\n")
                .arg(e.what())
            );
    }

    file.close();
}

void LSTMModel::load(const QString path, const QString fileName)
{
    // пытаемся открыть файл
    ifstream file;
    file.open(fileName.toStdString());
    if (!file.is_open()) {
        throw NeuralNetworkException(
            QString("Catch neural network model loading exception:\n[%1]\n")
                .arg("Failed to open file")
            );
    }
    // пытаемся загрузить данные модели
    try {
        string line;
        // построчно создаем слои по данным из файла
        while (getline(file, line)) {
            QString layerName = QString::fromStdString(line);
            _layers.push_back(new LSTMLayer(path, layerName));
        }
    } catch (const NeuralNetworkException &e) {
        throw NeuralNetworkException(
            QString("Catch neural network model loading layers exception:\n[%1]\n")
                .arg(e.what())
            );
    }

    file.close();
}

QList<INeuralNetworkLayer *> LSTMModel::layers() const
{
    return _layers;
}

Matrix3d<double> LSTMModel::forward(Matrix3d<double> batch)
{
    Matrix3d<double> predictionBatch;
    // обрабатываем входящие значения в предсказание сети
    for (INeuralNetworkLayer *layer : _layers) {
        predictionBatch = layer->forward(batch);
    }

    return predictionBatch;
}

Matrix3d<double> LSTMModel::backward(Matrix3d<double> gradient)
{
    Matrix3d<double> lossGradient;
    // обрабатываем градиент в обратном порядке
    for (int i = _layers.size()-1; i >= 0; --i) {
        _layers.value(i)->backward(gradient);
    }

    return lossGradient;
}

double LSTMModel::singleStep(Matrix3d<double> xBatch,
                             Matrix3d<double> yBatch)
{
    // 1) находим предсказание сети (прямой проход)
    Matrix3d<double> xBatchPrediction = forward(xBatch);
    // 2) высчитываем среднюю квадратичную потерю и градиент потерь
    double meanLoss = _loss->forward(&xBatchPrediction, &yBatch);
    Matrix3d<double> lossGradient(_loss->backward());
    // 3) чистка градиентов
    for (INeuralNetworkLayer *layer : _layers) {
        layer->clearGradients();
    }
    // 4) обратный проход (обновление параметров сети)
    backward(lossGradient);

    return meanLoss;
}
