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
    ///
    /// \brief expertTestSoftmaxCrossEntropyLoss
    /// расширенный тест потерь - анализ значений в
    /// зависимости от входных данных
    void expertTestSoftmaxCrossEntropyLoss();
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
    Matrix2d<double>::floorM(currentResult, 1000);
    vector<vector<double>> properResult{{0.843, 0.114, 0.042},
                                        {0.878, 0.002, 0.118},
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

void TestLoss::expertTestSoftmaxCrossEntropyLoss()
{
    // инициализация
    SoftmaxCrossEntropyLoss SCELoss;
    vector<vector<double>> target{{0.55,0.33,0.22},
                                  {0.78,0.67,0.11},
                                  {0.77,0.11,0.33}};
    vector<vector<double>> predictionOne{{5.55,3.33,2.12},
                                         {4.26,10.10,2.25},
                                         {3.33,1.19,7.12}};
    vector<vector<double>> predictionTwo{{5.45,3.14,2.12},
                                         {7.16,5.79,10.99},
                                         {6.98,1.09,3.14}};
    vector<vector<double>> predictionThree{{15.55,33.33,9.12},
                                           {14.26,10.10,9.25},
                                           {3.33,15.19,17.12}};
    // результаты (штрафы или потери)
    double resultPenaltyOne = SCELoss.forward(predictionOne, target);
    double resultPenaltyTwo = SCELoss.forward(predictionTwo, target);
    double resultPenaltyThree = SCELoss.forward(predictionThree, target);

    QCOMPARE(resultPenaltyTwo < resultPenaltyOne, true);
    QCOMPARE(resultPenaltyTwo < resultPenaltyThree, true);
    QCOMPARE(resultPenaltyOne < resultPenaltyThree, true);

    cout << resultPenaltyTwo << " "
         << resultPenaltyOne << " "
         << resultPenaltyThree;
}

QTEST_MAIN(TestLoss)
#include "testloss.moc"
