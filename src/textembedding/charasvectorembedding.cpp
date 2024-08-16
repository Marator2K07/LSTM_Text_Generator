#include "charasvectorembedding.h"
#include "matrix2d.cpp"
#include "matrix3d.cpp"

QList<QChar> CharAsVectorEmbedding::INVALID_CHARACTERS_WITHOUT_REPLACE {
    '~', '`', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    '@', '$', '%', '^', '&', '*', '+', '-', '_', '=', '#',
    '{', '}', '[', ']', '/', '\'', '|', ':', '"'
};

QList<QChar> CharAsVectorEmbedding::INVALID_CHARACTERS_WITH_REPLACE {
    '!', '?', ';'
};

void CharAsVectorEmbedding::processTheFile(QString fileName)
{
    // подготовка
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
    QString curText = removeInvalidCharacters(QString(filedata));
    unsigned long index = 0;
    for (unsigned long i = 0; i < curText.length(); ++i) {
        // определяем текущую букву
        QChar curChar(curText.at(i));
        if (curChar.isUpper()) {
            curChar = curChar.toLower();
        }
        // проверяем символ на наличие в словаре
        if (!_charToIdx.contains(curChar)) {
            _charToIdx.insert(curChar, index);
            _idxToChar.insert(index, curChar);
            index++;
        }
    }
    _text = curText;
    _vocabSize = _charToIdx.size();
}

QString CharAsVectorEmbedding::removeInvalidCharacters(const QString &text) const
{
    // подготовка
    long long index = -1;
    QString result{text};
    QString doubleSpace("  ");
    // первичная обработка на символы без замены
    for (const QChar &symbol : INVALID_CHARACTERS_WITHOUT_REPLACE) {
        // пытаемся найти
        index = result.indexOf(symbol);
        // пока такой символ существует
        while (index != -1) {
            result.removeAt(index);
            index = result.indexOf(symbol);
        }
    }
    // вторичная обработка на символы с заменой
    for (const QChar &symbol : INVALID_CHARACTERS_WITH_REPLACE) {
        // пытаемся найти
        index = result.indexOf(symbol);
        // пока такой символ существует
        while (index != -1) {
            result.replace(index, 1, QChar('.'));
            index = result.indexOf(symbol);
        }
    }
    // проверка на двойной пробел
    index = result.indexOf(doubleSpace);
    // удаляем лишний пробел
    while (index != -1) {
        result.removeAt(index);
        index = result.indexOf(doubleSpace);
    }

    return result;
}

CharAsVectorEmbedding::CharAsVectorEmbedding(QString filePath,
                                             QHash<int, QChar> idxToChar,
                                             QHash<QChar, int> charToIdx,
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

QChar CharAsVectorEmbedding::charForIndex(int index) const
{
    return _idxToChar.value(index);
}

int CharAsVectorEmbedding::indexForChar(QChar symbol) const
{
    return _charToIdx.value(symbol);
}

QList<int> CharAsVectorEmbedding::textToIndeces(const QString text)
{
    // подготовка
    QList<int> resultIndeces;
    // проходимся по тексту:
    for (int i = 0; i < text.size(); ++i) {
        QChar currentSymbol = text[i].toLower();
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
                _charToIdx[currentSymbol]
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

QList<QChar> CharAsVectorEmbedding::symbols() const
{
    return _charToIdx.keys();
}

QList<int> CharAsVectorEmbedding::indeces() const
{
    return _idxToChar.keys();
}
