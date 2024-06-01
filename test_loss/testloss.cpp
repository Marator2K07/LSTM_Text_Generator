#include <QObject>
#include <vector>
#include <QtTest/QtTest>

#include "activationfunctions.h"

using namespace std;

class TestLoss: public QObject
{
    Q_OBJECT

private slots:
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

void TestLoss::testSoftmax()
{
    // инициализация
    vector<double> init{5,3,2};
    // итоговый и ожидаемый результаты
    vector<double> currentResult = ActivationFunctions::softmax(init);
    for (double &value : currentResult) {
        value = round(value * 1000)/1000;
    }
    vector<double> properResult{0.844, 0.114, 0.042};

    QCOMPARE(currentResult, properResult);
}

void TestLoss::testBatchSoftmax()
{
    // инициализация
    vector<vector<double>> init{{5,3,2},
                                {7,1,5},
                                {3,1,4}};
    // итоговый и ожидаемый результаты
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

QTEST_MAIN(TestLoss)
#include "testloss.moc"
