#include "charasvectorembedding.h"

void CharAsVectorEmbedding::processTheFile(QString fileName)
{

}

CharAsVectorEmbedding::CharAsVectorEmbedding(int sequenceLength, int batchSize)
    : _sequenceLength{sequenceLength}
    , _batchSize{batchSize}
{
    processTheFile("text.txt");
}

CharAsVectorEmbedding::CharAsVectorEmbedding(QString fileName,
                                             int sequenceLength,
                                             int batchSize)
    : _sequenceLength{sequenceLength}
    , _batchSize{batchSize}
{
    processTheFile(fileName);
}

Matrix2d<int> CharAsVectorEmbedding::genTextIndices(int startPos)
{

}

Matrix3d<int> CharAsVectorEmbedding::genTextBanch(Matrix2d<int> indices)
{

}
