#include <QObject>
#include <vector>
#include <QtTest/QtTest>

#include <matrix2d.h>
#include <matrix3d.h>

using namespace std;

class TestMatrix: public QObject
{
    Q_OBJECT

private slots:
};

QTEST_MAIN(TestMatrix)
#include "testmatrix.moc"
