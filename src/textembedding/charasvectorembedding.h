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
    QHash<int, QChar> _idxToChar;
    QHash<QChar, int> _charToIdx;
    int _batchSize; // размер партии символов текста
    int _sequenceLength; // макс. длина последовательности для партии
    int _vocabSize; // найденный размер словаря

private:
    ///
    /// \brief processTheFile
    /// обработка заданного файла после открытия,
    /// а именно нахождения словаря и его размера
    /// + словарей символа к индексу и наоборот
    /// \param fileName полученный из файла текст
    void processTheFile(QString fileName);
    ///
    /// \brief removeInvalidCharacters
    /// чистка из текста, мешающих для обучения символов
    /// \param text текст для анализа
    /// \return обработанный текст
    QString removeInvalidCharacters(const QString &text) const;

public:
    CharAsVectorEmbedding(QString filePath,
                          QHash<int, QChar> idxToChar,
                          QHash<QChar, int> charToIdx,
                          int sequenceLength,
                          int batchSize);
    CharAsVectorEmbedding(QString fullFilePath,
                          int sequenceLength = 16,
                          int batchSize = 32);

    // списки недостумых символов в обучающих данных
    static QList<QChar> INVALID_CHARACTERS_WITH_REPLACE;
    static QList<QChar> INVALID_CHARACTERS_WITHOUT_REPLACE;
    //

public:
    // ITextEmbedding interface
    QString text() const override;
    QString filePath() const override;
    int batchSize() const override;
    int sequenceLength() const override;
    int vocabSize() const override;
    QChar charForIndex(int index) const override;
    int indexForChar(QChar symbol) const override;
    QList<QChar> symbols() const override;
    QList<int> indeces() const override;
    QList<int> textToIndeces(const QString text) override;
    Matrix2d<double> genTextIndices(int startPos) override;
    Matrix3d<double> genTextBatch(Matrix2d<double> indices) override;
    //

};

#endif // CHARASVECTOREMBEDDING_H
