#include "charasvectorembedding.h"

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
    for (int i = 0; i < filedata.length(); ++i) {
        _charToIdx.insert(filedata.at(i), filedata.at(i));
        _idxToChar.insert(filedata.at(i), filedata.at(i));
    }
    _text = QString(filedata);
}

template<typename T>
CharAsVectorEmbedding<T>::CharAsVectorEmbedding(int sequenceLength, int batchSize)
    : _sequenceLength{sequenceLength}
    , _batchSize{batchSize}
{
    processTheFile(QDir::currentPath() + "/text.txt");
}

template<typename T>
CharAsVectorEmbedding<T>::CharAsVectorEmbedding(QString fileName,
                                                int sequenceLength,
                                                int batchSize)
    : _sequenceLength{sequenceLength}
    , _batchSize{batchSize}
{
    processTheFile(QDir::currentPath() + '/' + fileName);
}

template<typename T>
QString CharAsVectorEmbedding<T>::text() const
{
    return _text;
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
Matrix2d<T> CharAsVectorEmbedding<T>::genTextIndices(int startPos)
{
    // создаем матрицу нужных размеров
    Matrix2d<T> textIndices
        = Matrix2d<T>::zeroM(_batchSize, _sequenceLength);
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

template<typename T>
Matrix3d<T> CharAsVectorEmbedding<T>::genTextBanch(Matrix2d<T> indices)
{

}
