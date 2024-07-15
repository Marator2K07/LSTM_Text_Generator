#include "charasvectorembedding.h"
#include "matrix2d.cpp"
#include "matrix3d.cpp"

template<typename T>
void CharAsVectorEmbedding<T>::processTheFile(QString fileName)
{
    QFile file(fileName);
    QByteArray filedata;
    // пытаемся открыть файл
    if (!file.open(QIODevice::ReadOnly)) {
        throw TextEmbeddingException(
            QString("Catch text embedding exception:\n[%1]\n")
                .arg("Failed to open file")
        );
    }
    // заполняем оставшиеся поля класса
    filedata = file.readAll();
    unsigned long index = 0;
    for (unsigned long i = 0; i < filedata.length(); ++i) {
        // буква со сдвигом
        char shiftChar = filedata.at(i)+_letterShift;
        // проверяем промежутки
        if (!_charToIdx.contains(shiftChar) &&
            !_charToIdx.contains(filedata.at(i))) {
            // если буква является английской заглавной
            if (filedata.at(i) >= _letterAIdx &&
                _letterZIdx >= filedata.at(i)) {
                cout << shiftChar << endl;
                _charToIdx.insert(shiftChar, index);
                _idxToChar.insert(index, shiftChar);
                index++;
                continue;
            }
            // остальные символы кроме заглавных англ. букв
            if (_rightIdxBorder >= filedata.at(i) &&
                _leftIdxBorder <= filedata.at(i)) {
                cout << filedata.at(i) << endl;
                _charToIdx.insert(filedata.at(i), index);
                _idxToChar.insert(index, filedata.at(i));
                index++;
            }
        }
    }
    _text = QString(filedata);
    _vocabSize = _charToIdx.size();
}

template<typename T>
CharAsVectorEmbedding<T>::CharAsVectorEmbedding(QString filePath,
                                                QMap<int, char> idxToChar,
                                                QMap<char, int> charToIdx,
                                                int sequenceLength,
                                                int batchSize)
    : _filePath{filePath}
    , _idxToChar{idxToChar}
    , _charToIdx{charToIdx}
    , _sequenceLength{sequenceLength}
    , _batchSize{batchSize}
{
    _vocabSize = idxToChar.size();
    processTheFile(filePath);
}

template<typename T>
CharAsVectorEmbedding<T>::CharAsVectorEmbedding(QString fullFilePath,
                                                int sequenceLength,
                                                int batchSize)
    : _filePath{fullFilePath}
    , _sequenceLength{sequenceLength}
    , _batchSize{batchSize}
{
    processTheFile(fullFilePath);
}

template<typename T>
QString CharAsVectorEmbedding<T>::text() const
{
    return _text;
}

template<typename T>
QString CharAsVectorEmbedding<T>::filePath() const
{
    return _filePath;
}

template<typename T>
int CharAsVectorEmbedding<T>::batchSize() const
{
    return _batchSize;
}

template<typename T>
int CharAsVectorEmbedding<T>::sequenceLength() const
{
    return _sequenceLength;
}

template<typename T>
int CharAsVectorEmbedding<T>::vocabSize() const
{
    return _vocabSize;
}

template<typename T>
QMap<int, char> CharAsVectorEmbedding<T>::idxToChar() const
{
    return _idxToChar;
}

template<typename T>
QMap<char, int> CharAsVectorEmbedding<T>::charToIdx() const
{
    return _charToIdx;
}

template<typename T>
vector<int> CharAsVectorEmbedding<T>::textToIndeces(const QString text)
{
    // подготовка
    vector<int> resultIndeces;
    // проходимся по тексту:
    for (int i = 0; i < text.size(); ++i) {
        char currentSymbol = text[i].toLatin1();
        // если эмбеддинг не содержит в словаре текущего символа
        if (!_charToIdx.contains(currentSymbol)) {
            throw TextEmbeddingException(
                QString("Catch text embedding exception:\n[%1]\n")
                    .arg("Unable to index symbol")
                );
        }
        // а если все впорядке
        resultIndeces.push_back(_charToIdx[currentSymbol]);
    }

    return resultIndeces;
}

template<typename T>
Matrix2d<T> CharAsVectorEmbedding<T>::genTextIndices(int startPos)
{
    // создаем матрицу нужных размеров
    Matrix2d<T> textIndices
        = Matrix2d<T>::zeroM(_batchSize, _sequenceLength);
    // ставим индексы символов из текста
    for (int i = 0; i < _batchSize; ++i) {
        int k = 0;
        for (int chIdx = startPos + i;
             chIdx < startPos + _sequenceLength + i;
             ++chIdx) {
            // если заглавная буква
            QChar currentSymbol = _text[chIdx];
            if (currentSymbol.isUpper()) {
                currentSymbol = currentSymbol.toLower();
            }
            // присваиваем значение
            textIndices.setValue(
                i,
                k++,
                _charToIdx[currentSymbol.toLatin1()]
            );
        }
    }

    return textIndices;
}

template<typename T>
Matrix3d<T> CharAsVectorEmbedding<T>::genTextBatch(Matrix2d<T> indices)
{
    // готовим будущий результат
    vector<Matrix2d<T>> resBatchData;
    for (vector row : indices.dataToVector()) {
        // подготовливаем подматрицу для заполнения
        Matrix2d<T> seqMatrix
            = Matrix2d<T>::zeroM(_sequenceLength, _vocabSize);
        // cтавим единицу в уникальном месте,
        // ради идентификации буквы как вектора
        for (int i = 0; i < _sequenceLength; ++i) {
            seqMatrix.setValue(i, row[i], 1);
        }
        // можно добавлять в данные партии
        resBatchData.push_back(seqMatrix);
    }

    return Matrix3d<T>(resBatchData);
}
