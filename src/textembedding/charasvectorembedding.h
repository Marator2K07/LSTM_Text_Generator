#ifndef CHARASVECTOREMBEDDING_H
#define CHARASVECTOREMBEDDING_H

#include "itextembedding.h"

///
/// \brief The CharAsVectorEmbedding class
/// классический эмбеддинг с представлением символа
/// как массива(вектора) цирф и размером в длину словаря
class CharAsVectorEmbedding : public ITextEmbedding
{
private:
    QString _text;
    QString _filePath;
    QHash<int, char> _idxToChar;
    QHash<char, int> _charToIdx;
    int _batchSize; // размер партии символов текста
    int _sequenceLength; // макс. длина последовательности для партии
    int _vocabSize; // найденный размер словаря
    int _leftIdxBorder = 32; // крайняя левая граница доступных индексов
    int _rightIdxBorder = 127; // крайняя прав. граница доступных индексов
    int _letterAIdx = 65; // индекс заглавной буквы А
    int _letterZIdx = 90; // индекс заглавной буквы Z
    int _letterShift = 32; // сдвиг буквы от заглавной к прописной

private:
    ///
    /// \brief processTheFile
    /// обработка заданного файла после открытия,
    /// а именно нахождения словаря и его размера
    /// + словарей символа к индексу и наоборот
    /// \param fileName полученный из файла текст
    void processTheFile(QString fileName);

public:
    CharAsVectorEmbedding(QString filePath,
                          QHash<int, char> idxToChar,
                          QHash<char, int> charToIdx,
                          int sequenceLength,
                          int batchSize);
    CharAsVectorEmbedding(QString fullFilePath,
                          int sequenceLength = 16,
                          int batchSize = 32);

public:
    // ITextEmbedding interface
    QString text() const override;
    QString filePath() const override;
    int batchSize() const override;
    int sequenceLength() const override;
    int vocabSize() const override;
    char charForIndex(int index) const override;
    int indexForChar(char symbol) const override;
    QList<char> symbols() const override;
    QList<int> indeces() const override;
    QList<int> textToIndeces(const QString text) override;
    Matrix2d<double> genTextIndices(int startPos) override;
    Matrix3d<double> genTextBatch(Matrix2d<double> indices) override;
    //

};

#endif // CHARASVECTOREMBEDDING_H
