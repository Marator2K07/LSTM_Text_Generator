#ifndef ITEXTEMBEDDING_H
#define ITEXTEMBEDDING_H

#include <vector>
#include "matrix2d.h"
#include "matrix3d.h"

using namespace std;

///
/// \brief The ITextEmbedding interface
/// определение функциональности преобразователя
/// текста в математическое представление
/// (набор вложенных векторов - или матрицы)
class ITextEmbedding
{
public:
    virtual Matrix2d<int> genInputIndices(int startPos) = 0;
    virtual Matrix2d<int> genTargetIndices(int startPos) = 0;
    virtual Matrix3d<int> genNewBanch(Matrix2d<int> indices) = 0;

public:
    virtual ~ITextEmbedding() {}
};

#endif // ITEXTEMBEDDING_H
