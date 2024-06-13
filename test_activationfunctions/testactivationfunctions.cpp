#include <QObject>
#include <QtTest/QtTest>

#include "activationfunctions.h"
#include "activationfunctions.cpp"

using namespace std;

class TestActivationFunctions: public QObject
{
    Q_OBJECT

private slots:
    ///
    /// \brief testSoftmax многопеременная логистическая
    /// функция, - более чувствительное отношение
    /// к максимальным значениям
    void testSoftmax();

};

void TestActivationFunctions::testSoftmax()
{
    // инициализация
    vector<int> init{5,3,2};
    // итоговый и ожидаемый результаты
    vector<double> currentResult = ActivationFunctions<int>::softmax(init);
    for (double &value : currentResult) {
        value = round(value * 1000)/1000;
    }
    vector<double> properResult{0.844, 0.114, 0.042};

    QCOMPARE(currentResult, properResult);
}

QTEST_MAIN(TestActivationFunctions)
#include "testactivationfunctions.moc"
