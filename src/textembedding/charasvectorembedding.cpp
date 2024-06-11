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

Matrix2d<int> CharAsVectorEmbedding::genTextIndices(int startPos)
{

}

Matrix3d<int> CharAsVectorEmbedding::genTextBanch(Matrix2d<int> indices)
{

}
