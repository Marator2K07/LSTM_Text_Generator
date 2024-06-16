#include <QObject>
#include <QtTest/QtTest>

#include "softmaxcrossentropyloss.h"
#include "softmaxcrossentropyloss.cpp"
#include "matrix2d.h"
#include "matrix2d.cpp"
#include "matrix3d.h"
#include "matrix3d.cpp"

using namespace std;

class TestLoss: public QObject
{
    Q_OBJECT

private slots:
    ///
    /// \brief testSoftmaxCrossEntropyLossFull тестирование
    /// вычисления штрафа сети и градиента входных данных
    void testSoftmaxCrossEntropyLossFull();
    ///
    /// \brief expertTestSoftmaxCrossEntropyLoss
    /// расширенный тест потерь - анализ значений в
    /// зависимости от входных данных
    void expertTestSoftmaxCrossEntropyLoss();
};

void TestLoss::testSoftmaxCrossEntropyLossFull()
{
    // инициализация
    SoftmaxCrossEntropyLoss SCELoss;
    Matrix2d<double> target{{0.55,0.33,0.22},
                            {0.78,0.67,0.11},
                            {0.77,0.11,0.33}};
    Matrix2d<double> predictionBad{{5,3},
                                   {7,6},
                                   {7,1}};
    Matrix2d<double> prediction{{5.55,3.33,2.12},
                                {4.26,10.10,2.25},
                                {3.33,1.19,7.12}};
    // результаты (штраф или потеря)
    double resultPenalty = SCELoss.forward(&prediction, &target);
    resultPenalty = floor(resultPenalty * 1000) / 1000;
    double properPenalty = 16.063;
    // результаты (градиент)
    auto resultGradient = SCELoss.backward();
    resultGradient->floorM(3);
    Matrix2d<double> properGradient{{0.326,-0.235,-0.192},
                                    {-0.778,0.326,-0.11},
                                    {-0.748,-0.108,0.645}};

    QCOMPARE(resultPenalty, properPenalty);
    QCOMPARE(resultGradient->data(), properGradient.data());

    // случай с исключением
    try {
        double resultPenalty = SCELoss.forward(&predictionBad, &target);
    } catch (const LossException &e) {
        cerr << e.what() << endl;
    }
}

void TestLoss::expertTestSoftmaxCrossEntropyLoss()
{
    // инициализация
    SoftmaxCrossEntropyLoss SCELoss;
    Matrix2d<double> target{{0.55,0.33,0.22},
                            {0.78,0.67,0.11},
                            {0.77,0.11,0.33}};
    Matrix2d<double> predictionOne{{5.55,3.33,2.12},
                                  {4.26,10.10,2.25},
                                  {3.33,1.19,7.12}};
    Matrix2d<double> predictionTwo{{5.45,3.14,2.12},
                                  {7.16,5.79,10.99},
                                  {6.98,1.09,3.14}};
    Matrix2d<double> predictionThree{{15.55,33.33,9.12},
                                    {14.26,10.10,9.25},
                                    {3.33,15.19,17.12}};
    // результаты (штрафы или потери)
    double resultPenaltyOne = SCELoss.forward(&predictionOne, &target);
    double resultPenaltyTwo = SCELoss.forward(&predictionTwo, &target);
    double resultPenaltyThree = SCELoss.forward(&predictionThree, &target);

    QCOMPARE(resultPenaltyTwo < resultPenaltyOne, true);
    QCOMPARE(resultPenaltyTwo < resultPenaltyThree, true);
    QCOMPARE(resultPenaltyOne < resultPenaltyThree, true);

    cout << resultPenaltyTwo << " "
         << resultPenaltyOne << " "
         << resultPenaltyThree;
}

QTEST_MAIN(TestLoss)
#include "testloss.moc"
