#ifndef CHARASVECTOREMBEDDING_H
#define CHARASVECTOREMBEDDING_H

#include <QMap>
#include <QFile>
#include <QByteArray>

#include "itextembedding.h"

///
/// \brief The CharAsVectorEmbedding class
/// классический эмбеддинг с представлением символа
/// как массива(вектора) цирф и размером в длину словаря
class CharAsVectorEmbedding : public ITextEmbedding
{
private:
    QString _text;
    QMap<int, QChar> idxToChar;
    QMap<QChar, int> charToIdx;
    int _batchSize; // размер партии символов текста
    int _sequenceLength; // макс. длина последовательности для партии
    int _vocabSize; // найденный размер словаря

private:
    ///
    /// \brief processTheFile
    /// обработка заданного текста после открытия,
    /// а именно нахождения словаря и его размера
    /// + словарей символа к индексу и наоборот
    /// \param text полученный из файла текст
    void processTheFile(QString text);

public:
    CharAsVectorEmbedding();
    CharAsVectorEmbedding(QString fileName);

public:
    // ITextEmbedding interface
    Matrix2d<int> genTextIndices(int startPos) override;
    Matrix3d<int> genTextBanch(Matrix2d<int> indices) override;
};

#endif // CHARASVECTOREMBEDDING_H
