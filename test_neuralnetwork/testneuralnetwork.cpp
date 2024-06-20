#include <QObject>
#include <QtTest/QtTest>
#include <QMapIterator>

#include "lstmnode.h"

using namespace std;

class TestNeuralNetwork: public QObject
{
    Q_OBJECT

private slots:

};

QTEST_MAIN(TestNeuralNetwork)
#include "testneuralnetwork.moc"
