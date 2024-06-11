#include <QObject>
#include <QtTest/QtTest>
#include <QMapIterator>

#include "charasvectorembedding.h"
#include "charasvectorembedding.cpp"

using namespace std;

class TestTextEmbedding: public QObject
{
    Q_OBJECT

private slots:
    ///
    /// \brief textFileProcessing
    /// тест для начальной корректной обработки
    /// данных при создании эксземпляров обькта
    void textFileProcessing();
    ///
    /// \brief testGenTextEmbeddingIndices
    /// тестирование генерации индексов символов в матрицу
    void testGenTextEmbeddingIndices();
};

void TestTextEmbedding::textFileProcessing()
{
    try {
        // инициализация
        CharAsVectorEmbedding<int> txtEmbed;
        // результаты
        for (int i = 0; i < txtEmbed.text().size(); ++i) {
            cout << txtEmbed.charToIdx().value(txtEmbed.text()[i].toLatin1()) << " ";
        }
        QCOMPARE(txtEmbed.charToIdx().size(), txtEmbed.idxToChar().size());
        QCOMPARE(txtEmbed.text().size() > txtEmbed.idxToChar().size(), true);
        QCOMPARE(txtEmbed.text().size() > txtEmbed.charToIdx().size(), true);
        QCOMPARE(txtEmbed.charToIdx()['1']
                     == txtEmbed.charToIdx()[txtEmbed.idxToChar()[0]], true);
        QCOMPARE(txtEmbed.charToIdx()['w']
                     == txtEmbed.charToIdx()[txtEmbed.idxToChar()[2]], true);
        QCOMPARE(txtEmbed.charToIdx()['f']
                     == txtEmbed.charToIdx()[txtEmbed.idxToChar()[7]], false);

    } catch (const TextEmbeddingException &e) {
        cout << e.what() << endl;
    }
}

void TestTextEmbedding::testGenTextEmbeddingIndices()
{
    try {
        // инициализация
        CharAsVectorEmbedding<double> txtEmbed("Plain_Kate.txt", 32, 16);
        // результаты
        Matrix2d<double> resIndices = txtEmbed.genTextIndices(0);
        QString str = "Erin Bow";
        for (int i= 0; i < str.size(); ++i) {
            QCOMPARE(txtEmbed.idxToChar()[i], str[i].toLatin1());
        }
        // информация для анализа
        QMapIterator<int, char> it(txtEmbed.idxToChar());
        while (it.hasNext()) {
            it.next();
            cout << it.key() << ": " << it.value() << endl;
        }
        resIndices.print();
    } catch (const TextEmbeddingException &e) {
        cout << e.what() << endl;
    }
}

QTEST_MAIN(TestTextEmbedding)
#include "testtextembedding.moc"
