#include <QObject>
#include <QtTest/QtTest>

#include "sgd.h"
#include "lstmmodel.h"
#include "lstmlayer.h"
#include "softmaxcrossentropyloss.h"
#include "charasvectorembedding.h"
#include "charasvectorembedding.cpp"

using namespace std;

class TestOptimizer: public QObject
{
    Q_OBJECT

private slots:

};

QTEST_MAIN(TestOptimizer)
#include "testoptimizer.moc"
