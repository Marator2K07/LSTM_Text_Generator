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
    Matrix3d<double> target {{{0.5,0.3,0.2},{0.2,0.3,0.1},{0.6,0.1,0.8}},
                            {{0.8,0.2,0.1},{0.5,0.6,0.1}, {0.2,0.2,0.8}}};
    Matrix3d<double> predictionBad{{{5,3},
                                    {7,6},
                                    {7,1}}};
    Matrix3d<double> prediction {{{1.5,2.3,1.2},{3.2,1.33,2.1},{1.6,3.1,2.8}},
                                 {{2.8,1.2,2.1},{1.5,2.6,1.1}, {2.2,1.22,1.8}}};
    // результаты (штраф или потеря)
    double resultPenalty = SCELoss.forward(&prediction, &target);
    resultPenalty = floor(resultPenalty * 1000) / 1000;
    double properPenalty = 12.745;
    // результаты (градиент)
    Matrix3d<double> resultGradient(SCELoss.backward()->data());
    Matrix3d<double> properGradient {{{-0.24787961,0.26110424,-0.01322462},
                                     {0.47249733,-0.19635225,0.12385492},
                                     {-0.48638695,0.40917835,-0.4227914}},
                                    {{-0.21123892,-0.08113119,0.1923701},
                                     {-0.28607274,0.04267301,0.04339973},
                                     {0.28884668,-0.01653041,-0.47231627}}};

    QCOMPARE(resultPenalty, properPenalty);
    QCOMPARE(resultGradient.compareDoubles(&properGradient, 1e-7), true);

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
