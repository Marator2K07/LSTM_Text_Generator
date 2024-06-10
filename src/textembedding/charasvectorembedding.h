#ifndef CHARASVECTOREMBEDDING_H
#define CHARASVECTOREMBEDDING_H

#include "itextembedding.h"

///
/// \brief The CharAsVectorEmbedding class
/// классический эмбеддинг с представлением символа
/// как массива(вектора) цирф и размером в длину словаря
class CharAsVectorEmbedding : public ITextEmbedding
{
public:
    CharAsVectorEmbedding();

public:
    // ITextEmbedding interface
    Matrix2d<int> genTextIndices(int startPos) override;
    Matrix3d<int> genTextBanch(Matrix2d<int> indices) override;
};

#endif // CHARASVECTOREMBEDDING_H
