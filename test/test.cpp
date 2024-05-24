#include <QObject>
#include <QtTest/QtTest>

#include "simplenum.h"
#include "numwithgradient.h"

class Test : public QObject
{
    Q_OBJECT

private slots:
    ///
    /// \brief testNumWithGradientOne составление
    /// простого 'уравнения' и его тестирование с помощью
    /// нахождения градиента (производной)
    void testNumWithGradientOne();
};

void Test::testNumWithGradientOne()
{
    NumWithGradient a(3);

    SimpleNum forB(4);
    NumWithGradient b(a * (Num *)(&forB));

    SimpleNum forC(5);
    NumWithGradient c(b + (Num *)(&forC));

    c.backward();

    double answer = 4;
    QCOMPARE(answer, a.gradient());
}

QTEST_MAIN(Test)
#include "test.moc"
