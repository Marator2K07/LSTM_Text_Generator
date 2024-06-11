#include "charasvectorembedding.h"

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
    for (int i = 0; i < filedata.length(); ++i) {
        _charToIdx.insert(filedata.at(i), filedata.at(i));
        _idxToChar.insert(filedata.at(i), filedata.at(i));
    }
    _text = QString(filedata);
}

CharAsVectorEmbedding::CharAsVectorEmbedding(int sequenceLength, int batchSize)
    : _sequenceLength{sequenceLength}
    , _batchSize{batchSize}
{
    processTheFile(QDir::currentPath() + "/text.txt");
}

CharAsVectorEmbedding::CharAsVectorEmbedding(QString fileName,
                                             int sequenceLength,
                                             int batchSize)
    : _sequenceLength{sequenceLength}
    , _batchSize{batchSize}
{
    processTheFile(QDir::currentPath() + '/' + fileName);
}

QString CharAsVectorEmbedding::text() const
{
    return _text;
}

QMap<int, char> CharAsVectorEmbedding::idxToChar() const
{
    return _idxToChar;
}

QMap<char, int> CharAsVectorEmbedding::charToIdx() const
{
    return _charToIdx;
}

Matrix2d<int> CharAsVectorEmbedding::genTextIndices(int startPos)
{
    // создаем матрицу нужных размеров
    Matrix2d<int> textIndices
        = Matrix2d<int>::zeroM(_batchSize, _sequenceLength);
    // заранее смотрим, выходим ли за пределы текста перед алгоритмом
    if (startPos + _sequenceLength + _batchSize + 1 > _text.length()) {
        startPos = _text.length() - startPos;
    }
    // ставим индексы символов из текста
    for (int i = 0; i < _batchSize; ++i) {
        int k = 0;
        for (int chIdx = startPos + i;
             chIdx < startPos + _sequenceLength + i;
             ++chIdx) {
            textIndices.setValue(i, k++, _charToIdx[_text[chIdx].toLatin1()]);
        }
    }

    return textIndices;
}

Matrix3d<int> CharAsVectorEmbedding::genTextBanch(Matrix2d<int> indices)
{

}
