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
    void testNumWithGradientTwo();
};

void Test::testNumWithGradientOne()
{
    NumWithGradient a(3);

    SimpleNum forB(4);
    NumWithGradient b(a * (Num *)(&forB));

    SimpleNum forC(5);
    NumWithGradient c(b + (Num *)(&forC));

    c.backward();

    // на данный момент у нас уравнение вида:
    // c = (a * 4) + 5, где при а = 3, градиент = 4
    double answer = 4;
    QCOMPARE(answer, a.gradient());
}

void Test::testNumWithGradientTwo()
{
    NumWithGradient a(3);

    SimpleNum forB(4);
    NumWithGradient b(a * (Num *)(&forB));

    SimpleNum forC(3);
    NumWithGradient c(b + (Num *)(&forC));

    SimpleNum forD(2);
    NumWithGradient d(a + (Num *)(&forD));

    NumWithGradient e(c * (Num *)&d);

    e.backward();

    double answer = 35;
    QCOMPARE(answer, a.gradient());
}

QTEST_MAIN(Test)
#include "test.moc"
