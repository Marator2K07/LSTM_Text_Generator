#include <QObject>
#include <QtTest/QtTest>

#include "activationfunctions.h"
#include "activationfunctions.cpp"

using namespace std;

class TestActivationFunctions: public QObject
{
    Q_OBJECT

private slots:

};

QTEST_MAIN(TestActivationFunctions)
#include "testactivationfunctions.moc"
