#include <QObject>
#include <QtTest/QtTest>

#include "charasvectorembedding.h"

using namespace std;

class TestTextEmbedding: public QObject
{
    Q_OBJECT

private slots:

};

QTEST_MAIN(TestTextEmbedding)
#include "testtextembedding.moc"
