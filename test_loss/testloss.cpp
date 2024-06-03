#include <QObject>
#include <vector>
#include <QtTest/QtTest>

#include "activationfunctions.h"
#include "softmaxcrossentropyloss.h"

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
    ///
    /// \brief testLossCalculate тестирование
    /// вычисления штрафа сети в виде double числа
    /// при прямом проходе
    void testSoftmaxCrossEntropyLossForward();
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

void TestLoss::testSoftmaxCrossEntropyLossForward()
{
    // инициализация
    SoftmaxCrossEntropyLoss SCELoss;
    vector<vector<double>> target{{5,3,2},
                                  {7,6,11},
                                  {7,1,3}};
    vector<vector<double>> predictionBad{{5,3},
                                         {7,6},
                                         {7,1}};
    vector<vector<double>> prediction{{5.55,3.33,2.12},
                                      {4.26,10.10,2.25},
                                      {3.33,1.19,7.12}};
    // результаты
    double resultPenalty = SCELoss.forward(prediction, target);
    resultPenalty = floor(resultPenalty * 1000) / 1000;
    double properPenalty = 130.139;

    QCOMPARE(resultPenalty, properPenalty);

    try {
        double resultPenalty = SCELoss.forward(predictionBad, target);

        // Т.к. код до сюда не дойдет, тест будет пройден
        QCOMPARE(resultPenalty, properPenalty);
    } catch (const LossException &e) {
        cerr << e.what() << endl;
    }
}

QTEST_MAIN(TestLoss)
#include "testloss.moc"
