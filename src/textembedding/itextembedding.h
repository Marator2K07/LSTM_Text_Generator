#ifndef ITEXTEMBEDDING_H
#define ITEXTEMBEDDING_H

#include <vector>

using namespace std;

///
/// \brief The ITextEmbedding interface
/// определение функциональности преобразователя
/// какой-то абстрактной информации(текста) в математическое
/// представление (набор векторов - или матрицы)
class ITextEmbedding
{
public:
    virtual vector<vector<int>> genInputIndices(int startPos) = 0;
    virtual vector<vector<int>> genTargetIndices(int startPos) = 0;
    virtual vector<vector<vector<int>>>
    genNewBanch(vector<vector<int>> indices) = 0;

public:
    virtual ~ITextEmbedding() {}
};

#endif // ITEXTEMBEDDING_H
