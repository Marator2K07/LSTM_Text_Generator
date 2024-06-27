#ifndef ITEXTEMBEDDING_H
#define ITEXTEMBEDDING_H

#include <QDir>
#include <QMap>
#include <QFile>
#include <QByteArray>
#include <vector>

#include "textembeddingexception.h"
#include "matrix2d.h"
#include "matrix3d.h"

using namespace std;

///
/// \brief The ITextEmbedding interface
/// определение функциональности преобразователя
/// текста в математическое представление
/// (набор вложенных векторов - или матрицы)
template<typename T>
class ITextEmbedding
{
public:
    ///
    /// \brief vocabSize размер словаря после анализа текста
    /// \return текущий размер словаря
    virtual int vocabSize() const = 0;
    ///
    /// \brief idxToChar геттер словаря индексов и букв для них
    /// \return словарь индекс->буква
    virtual QMap<int, char> idxToChar() const = 0;
    ///
    /// \brief charToIdx геттер словаря букв и индексов для них
    /// \return словарь буква->индекс
    virtual QMap<char, int> charToIdx() const = 0;
    ///
    /// \brief genTextIndices генерация 2д матрицы
    /// индексов символов для заданного текста
    /// \param startPos точка старта генерации
    /// \return 2д матрица с индексами символов текста
    virtual Matrix2d<T> genTextIndices(int startPos) = 0;
    ///
    /// \brief genTextBatch генерация партии (3д матрицы)
    /// представлений символов для заданного текста
    /// \param indices 2д матрица индексов символов текста
    /// \return 3д матрица с матем. представлениями символов текста
    virtual Matrix3d<T> genTextBatch(Matrix2d<T> indices) = 0;

public:
    virtual ~ITextEmbedding() {}
};

#endif // ITEXTEMBEDDING_H
