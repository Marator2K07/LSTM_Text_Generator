#include "charasvectorembedding.h"
#include "matrix2d.cpp"
#include "matrix3d.cpp"

void CharAsVectorEmbedding::processTheFile(QString fileName)
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

CharAsVectorEmbedding::CharAsVectorEmbedding(QString filePath,
                                             QHash<int, char> idxToChar,
                                             QHash<char, int> charToIdx,
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

CharAsVectorEmbedding::CharAsVectorEmbedding(QString fullFilePath,
                                             int sequenceLength,
                                             int batchSize)
    : _filePath{fullFilePath}
    , _sequenceLength{sequenceLength}
    , _batchSize{batchSize}
{
    processTheFile(fullFilePath);
}

QString CharAsVectorEmbedding::text() const
{
    return _text;
}

QString CharAsVectorEmbedding::filePath() const
{
    return _filePath;
}

int CharAsVectorEmbedding::batchSize() const
{
    return _batchSize;
}

int CharAsVectorEmbedding::sequenceLength() const
{
    return _sequenceLength;
}

int CharAsVectorEmbedding::vocabSize() const
{
    return _vocabSize;
}

char CharAsVectorEmbedding::charForIndex(int index) const
{
    return _idxToChar.value(index);
}

int CharAsVectorEmbedding::indexForChar(char symbol) const
{
    return _charToIdx.value(symbol);
}

vector<int> CharAsVectorEmbedding::textToIndeces(const QString text)
{
    // подготовка
    vector<int> resultIndeces;
    // проходимся по тексту:
    for (int i = 0; i < text.size(); ++i) {
        char currentSymbol = text[i].toLower().toLatin1();
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

Matrix2d<double> CharAsVectorEmbedding::genTextIndices(int startPos)
{
    // создаем матрицу нужных размеров
    Matrix2d<double> textIndices
        = Matrix2d<double>::zeroM(_batchSize, _sequenceLength);
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

Matrix3d<double> CharAsVectorEmbedding::genTextBatch(Matrix2d<double> indices)
{
    // готовим будущий результат
    vector<Matrix2d<double>> resBatchData;
    for (vector row : indices.dataToVector()) {
        // подготовливаем подматрицу для заполнения
        Matrix2d<double> seqMatrix
            = Matrix2d<double>::zeroM(_sequenceLength, _vocabSize);
        // cтавим единицу в уникальном месте,
        // ради идентификации буквы как вектора
        for (int i = 0; i < _sequenceLength; ++i) {
            seqMatrix.setValue(i, row[i], 1);
        }
        // можно добавлять в данные партии
        resBatchData.push_back(seqMatrix);
    }

    return Matrix3d<double>(resBatchData);
}
