#include <QObject>
#include <QtTest/QtTest>

#include "sgd.h"

using namespace std;

class TestOptimizer: public QObject
{
    Q_OBJECT

private slots:

};

QTEST_MAIN(TestOptimizer)
#include "testoptimizer.moc"
