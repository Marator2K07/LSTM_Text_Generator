#include <QObject>
#include <QtTest/QtTest>

#include "charasvectorembedding.h"

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
};

void TestTextEmbedding::textFileProcessing()
{
    try {
        // инициализация
        CharAsVectorEmbedding txtEmbed;
        // результаты
        QCOMPARE(txtEmbed.charToIdx().size(), txtEmbed.idxToChar().size());
        QCOMPARE(txtEmbed.text().size() > txtEmbed.idxToChar().size(), true);
        QCOMPARE(txtEmbed.text().size() > txtEmbed.charToIdx().size(), true);
        QCOMPARE(txtEmbed.charToIdx()['1'] == txtEmbed.idxToChar()[49], true);
        QCOMPARE(txtEmbed.charToIdx()['1'] == txtEmbed.idxToChar()[50], false);
        for (int i = 0; i < txtEmbed.text().size(); ++i) {
            cout << txtEmbed.charToIdx().value(txtEmbed.text()[i].toLatin1()) << " ";
        }
    } catch (const TextEmbeddingException &e) {
        cout << e.what() << endl;
    }
}

QTEST_MAIN(TestTextEmbedding)
#include "testtextembedding.moc"
