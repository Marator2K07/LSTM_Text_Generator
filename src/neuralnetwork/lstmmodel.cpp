#include "lstmmodel.h"
#include "charasvectorembedding.cpp"

QString LSTMModel::LAYERS_DATA_NAME = "layersData";
QString LSTMModel::EMBEDDING_DATA_NAME = "embeddingData";

LSTMModel::LSTMModel(QString name,
                     ILoss *loss,
                     ITextEmbedding<double> *embedding,
                     QList<INeuralNetworkLayer *> layers)
    : _name{name}
    , _loss{loss}
    , _embedding{embedding}
    , _layers{layers}
{
}

LSTMModel::LSTMModel(const QString path, const QString modelName, ILoss *loss)
    : _name{modelName}
    , _loss{loss}
{
    QString pathModel = QString("%1/%2").arg(path, modelName);
    load(pathModel);
}

LSTMModel::~LSTMModel()
{
}

bool LSTMModel::operator==(const LSTMModel model)
{
    // смотрим совпадает ли количество слоев в моделях
    if (_layers.size() != model.layers().size()) {
        return false;
    }
    // если все впорядке, то сравниваем послойно
    for (int i = 0; i < _layers.size(); ++i) {
        LSTMLayer *currentLayer = (LSTMLayer *)_layers.value(i);
        INeuralNetworkLayer *otherLayer = (LSTMLayer *)_layers.value(i);
        if (!currentLayer->compareLayer(otherLayer)) {
            return false;
        }
    }
    // если и тут все впорядке, то готовим данные для сравнения эмбеддинга
    QList<int> thisIndeces = _embedding->idxToChar().keys();
    QList<char> thisChars = _embedding->charToIdx().keys();
    QList<int> otherIndeces = model._embedding->idxToChar().keys();
    QList<char> otherChars = model._embedding->charToIdx().keys();
    // пытаемся сравнить
    try {
        for (int i = 0; i < _embedding->vocabSize(); ++i) {
            if (thisIndeces[i] != otherIndeces[i] ||
                thisChars[i] != otherChars[i]) {
                return false;
            }
        }
    } catch (...) {
        return false;
    }

    return true;
}

void LSTMModel::save(const QString path, bool inNewFolder)
{
    // подготовка
    QString fileNameLayers;
    QString fileNameEmbedding;
    QString folderPath;
    // в зависимости от флага создания новой папки
    if (inNewFolder) {
        // создаем новую папку в указанном месте
        folderPath = QString("%1/%2").arg(path, _name);
        QDir dir;
        dir.mkdir(folderPath);
        // полный путь до файла слоев
        fileNameLayers = QString("%1/%2_%3.txt")
                             .arg(folderPath, _name, LAYERS_DATA_NAME);
    } else {
        folderPath = QString("%1").arg(path);
        // полный путь до файла слоев
        fileNameLayers = QString("%1_%2.txt")
                             .arg(_name, LAYERS_DATA_NAME);
    }
    // пытаемся открыть файл для сохранения в новой папке данных о слоях
    ofstream fileLayers;
    fileLayers.open(fileNameLayers.toStdString());
    if (!fileLayers.is_open()) {
        throw NeuralNetworkException(
            QString("Catch neural network model saving layers data exception:\n[%1]\n")
                .arg("Failed to open file")
            );
    }
    // пишем информацию о слоях и одновременно пишем имена слоев в файл
    try {
        for (INeuralNetworkLayer *layer : _layers) {
            fileLayers << layer->name().toStdString() << endl;
            layer->saveParams(folderPath);
        }
    } catch (const NeuralNetworkException &e) {
        throw NeuralNetworkException(
            QString("Catch neural network model saving layers exception:\n[%1]\n")
                .arg(e.what())
            );
    }
    // закрываем файл
    fileLayers.close();
    // в зависимости от флага создания новой папки
    if (inNewFolder) {
        // полный путь до файла эмбеддинга
        fileNameEmbedding = QString("%1/%2_%3.txt")
                                .arg(folderPath, _name, EMBEDDING_DATA_NAME);
    } else {
        // полный путь до файла эмбеддинга
        fileNameEmbedding = QString("%1_%2.txt")
                                .arg(_name, EMBEDDING_DATA_NAME);
    }
    // пытаемся открыть файл для сохранения в новой папке данных о текущем эмбеддинге
    ofstream fileEmbedding;
    fileEmbedding.open(fileNameEmbedding.toStdString());
    if (!fileEmbedding.is_open()) {
        throw NeuralNetworkException(
            QString("Catch neural network model saving embedding data exception:\n[%1]\n")
                .arg("Failed to open file")
            );
    }
    // пишем главную эмбеддинговую информацию
    fileEmbedding << _embedding->filePath().toStdString() << " "
                  << _embedding->batchSize() << " "
                  << _embedding->sequenceLength() << " "
                  << _embedding->vocabSize() << endl;
    QList<char> symbols = _embedding->charToIdx().keys();
    QList<int> indeces = _embedding->charToIdx().values();
    for (int i = 0; i < _embedding->vocabSize(); ++i) {
        fileEmbedding << symbols[i] << indeces[i] << endl;
    }
    // закрываем файл
    fileEmbedding.close();
}

void LSTMModel::load(const QString path)
{
    // пытаемся открыть файл с данными о слоях
    QString layersDataFile = QString("%1/%2_%3.txt").
                             arg(path, _name, LAYERS_DATA_NAME);
    ifstream fileLayersStream;
    fileLayersStream.open(layersDataFile.toStdString());
    if (!fileLayersStream.is_open()) {
        throw NeuralNetworkException(
            QString("Catch neural network model loading layers data exception:\n[%1]\n")
                .arg("Failed to open file")
            );
    }
    // пытаемся загрузить данные модели для слоев
    try {
        string line;
        // построчно создаем слои по данным из файла
        while (getline(fileLayersStream, line)) {
            QString layerName = QString::fromStdString(line);
            _layers.push_back(new LSTMLayer(path, layerName));
        }
    } catch (const NeuralNetworkException &e) {
        throw NeuralNetworkException(
            QString("Catch neural network model loading layers exception:\n[%1]\n")
                .arg(e.what())
            );
    }
    // закрываем файл
    fileLayersStream.close();
    // пытаемся открыть файл с данными об эмбеддинге
    QString embeddingDataFile = QString("%1/%2_%3.txt").
                                arg(path, _name, EMBEDDING_DATA_NAME);
    ifstream fileEmbeddingStream;
    fileEmbeddingStream.open(embeddingDataFile.toStdString());
    if (!fileEmbeddingStream.is_open()) {
        throw NeuralNetworkException(
            QString("Catch neural network model loading embedding data exception:\n[%1]\n")
                .arg("Failed to open file")
            );
    }
    // готовим данные для конструктора эмбеддинга
    QMap<int, char> idxToChar;
    QMap<char, int> charToIdx;
    string filePath;
    int sequenceLength;
    int batchSize;
    // пытаемся загрузить его данные
    try {
        string line;
        // сначала считываем путь до файла,
        // размеры партии и последовательности
        getline(fileEmbeddingStream, line);
        istringstream rowStreamMain(line);
        rowStreamMain >> filePath >> batchSize >> sequenceLength;
        // заполняем словари        
        while (getline(fileEmbeddingStream, line)) {
            istringstream rowStream(line);
            // считываем данные строки
            char symbol;
            int index;
            rowStream >> noskipws >> symbol >> index;
            // и пишем их в словари
            idxToChar.insert(index, symbol);
            charToIdx.insert(symbol, index);
        }
        // создаем эмбеддинг на основе данных
        _embedding = new CharAsVectorEmbedding<double>(
            QString::fromStdString(filePath),
            idxToChar, charToIdx,
            sequenceLength, batchSize
            );
    } catch (const NeuralNetworkException &e) {
        throw NeuralNetworkException(
            QString("Catch neural network model loading embedding exception:\n[%1]\n")
                .arg(e.what())
            );
    }
    // закрываем файл
    fileEmbeddingStream.close();
}

QString LSTMModel::name() const
{
    return _name;
}

int LSTMModel::power() const
{
    // находим общую мощность слоев
    int totalLayersPower = 0;
    for (INeuralNetworkLayer *layer : _layers) {
        totalLayersPower += layer->power();
    }
    // и при возврате еще учитывается размер партии
    return totalLayersPower * _embedding->batchSize();
}

ITextEmbedding<double> *LSTMModel::embedding() const
{
    return _embedding;
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
