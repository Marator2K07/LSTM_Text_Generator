#ifndef CHARASVECTOREMBEDDING_H
#define CHARASVECTOREMBEDDING_H

#include "itextembedding.h"

///
/// \brief The CharAsVectorEmbedding class
/// классический эмбеддинг с представлением символа
/// как массива(вектора) цирф и размером в длину словаря
template<typename T>
class CharAsVectorEmbedding : public ITextEmbedding<T>
{
private:
    QString _text;
    QMap<int, char> _idxToChar;
    QMap<char, int> _charToIdx;
    int _batchSize; // размер партии символов текста
    int _sequenceLength; // макс. длина последовательности для партии
    int _vocabSize; // найденный размер словаря
    int _leftIdxBorder = 32; // крайняя левая граница доступных индексов
    int _rightIdxBorder = 127; // крайняя прав. граница доступных индексов

private:
    ///
    /// \brief processTheFile
    /// обработка заданного файла после открытия,
    /// а именно нахождения словаря и его размера
    /// + словарей символа к индексу и наоборот
    /// \param fileName полученный из файла текст
    void processTheFile(QString fileName);

public:
    CharAsVectorEmbedding(int sequenceLength = 16, int batchSize = 32);
    CharAsVectorEmbedding(QString fileName,
                          int sequenceLength = 16,
                          int batchSize = 32);

public:
    QString text() const;

    // ITextEmbedding interface    
    int vocabSize() const override;
    QMap<int, char> idxToChar() const override;
    QMap<char, int> charToIdx() const override;
    Matrix2d<T> genTextIndices(int startPos) override;
    Matrix3d<T> genTextBatch(Matrix2d<T> indices) override;
    //

};

#endif // CHARASVECTOREMBEDDING_H
