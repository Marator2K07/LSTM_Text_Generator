#include <QObject>
#include <vector>
#include <QtTest/QtTest>

#include "simplenum.h"
#include "numwithgradient.h"
#include "activationfunctions.h"

using namespace std;

class Test : public QObject
{
    Q_OBJECT

private:
    ///
    /// \brief forwardFuncForTestTwo имитация решения
    /// уравнения вида 4a^2 + 11a + 6 для использования
    ///  в тестируемом методе testNumWithGradientTwo
    /// \param num зависимая переменная уравнения
    double forwardFuncForTestTwo(double num);

private slots:
    ///
    /// \brief testNumWithGradientOne составление
    /// простого 'уравнения' и его тестирование с помощью
    /// нахождения градиента (производной)
    void testNumWithGradientOne();
    ///
    /// \brief testNumWithGradientTwo составляем уже более
    /// сложное 'уравнение' и его тестирование с помощью
    /// нахождения градиента (производной)
    void testNumWithGradientTwo();

    ///
    /// \brief testSoftmax многопеременная логистическая
    /// функция, - более чувствительное отношение
    /// к максимальным значениям
    void testSoftmax();
    ///
    /// \brief testBatchSoftmax расширенный тест для
    /// обработки партии предсказаний
    void testBatchSoftmax();
};

double Test::forwardFuncForTestTwo(double num)
{
    double b = num * 4;
    double c = b + 3;
    return c * (num + 2);
}

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

    // на данный у нас есть уравнение типа:
    // d = (4a + 3) * (a + 2) = 4a^2 + 11a + 6,
    // где производная dd/da = 8a + 11;
    // тогда при a = 3 - градиент = 8 * 3 + 11 = 35;
    double answer = 35;
    // также можно найти производную 'вручную', используя
    // составленный специально для этого примера метод
    double answerOther = ((forwardFuncForTestTwo(3.01)
                          - forwardFuncForTestTwo(2.99))
                          / 0.02);

    QCOMPARE(answer, a.gradient());
    QCOMPARE(answerOther, a.gradient());
}

void Test::testSoftmax()
{
    vector<double> init{5,3,2};
    vector<double> currentResult
        = ActivationFunctions::softmax(init);
    for (double &value : currentResult) {
        value = round(value * 1000)/1000;
    }

    vector<double> properResult{0.844, 0.114, 0.042};
    QCOMPARE(currentResult, properResult);
}

void Test::testBatchSoftmax()
{
    vector<vector<double>> init{{5,3,2},
                                {7,1,5},
                                {3,1,4}};
    vector<vector<double>> currentResult
        = ActivationFunctions::batchSoftmax(init);
    for (vector<double> &p : currentResult) {
        for (double &value : p) {
            value = round(value * 1000)/1000;
        }
    }

    vector<vector<double>> properResult{{0.844, 0.114, 0.042},
                                        {0.879, 0.002, 0.119},
                                        {0.259, 0.035, 0.705}};
    QCOMPARE(currentResult, properResult);
}

QTEST_MAIN(Test)
#include "test.moc"
