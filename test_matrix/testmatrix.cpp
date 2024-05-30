#include <QObject>
#include <QtTest/QtTest>

#include <matrix.h>

using namespace std;

class TestMatrix: public QObject
{
    Q_OBJECT

private slots:
};

QTEST_MAIN(TestMatrix)
#include "testmatrix.moc"
