#include <QObject>
#include <QtTest/QtTest>

#include "sgd.h"
#include "lstmmodel.h"
#include "softmaxcrossentropyloss.h"
#include "charasvectorembedding.h"

using namespace std;

class TestTrainer: public QObject
{
    Q_OBJECT

private slots:

};

QTEST_MAIN(TestTrainer)
#include "testtrainer.moc"
