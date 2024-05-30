#include <QObject>
#include <vector>
#include <QtTest/QtTest>

#include <matrix2d.h>
#include <matrix3d.h>

using namespace std;

class TestMaths: public QObject
{
    Q_OBJECT

private slots:
};

QTEST_MAIN(TestMaths)
#include "testmaths.moc"
