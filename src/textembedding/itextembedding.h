#ifndef ITEXTEMBEDDING_H
#define ITEXTEMBEDDING_H

#include <QDir>
#include <QMap>
#include <QFile>
#include <QByteArray>
#include <vector>

#include "textembeddingexception.h"
#include "matrix2d.h"
#include "matrix2d.cpp"
#include "matrix3d.h"
#include "matrix3d.cpp"

using namespace std;

///
/// \brief The ITextEmbedding interface
/// определение функциональности преобразователя
/// текста в математическое представление
/// (набор вложенных векторов - или матрицы)
class ITextEmbedding
{
public:
    ///
    /// \brief genTextIndices генерация 2д матрицы
    /// индексов символов для заданного текста
    /// \param startPos точка старта генерации
    /// \return 2д матрица с индексами символов текста
    virtual Matrix2d<int> genTextIndices(int startPos) = 0;
    ///
    /// \brief genTextBanch генерация партии (3д матрицы)
    /// представлений символов для заданного текста
    /// \param indices 2д матрица индексов символов текста
    /// \return 3д матрица с матем. представлениями символов текста
    virtual Matrix3d<int> genTextBanch(Matrix2d<int> indices) = 0;

public:
    virtual ~ITextEmbedding() {}
};

#endif // ITEXTEMBEDDING_H
