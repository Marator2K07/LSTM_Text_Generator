#include <QObject>
#include <QtTest/QtTest>

#include "activationfunctions.h"
#include "activationfunctions.cpp"
#include "matrix2d.h"
#include "matrix3d.h"

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
    ///
    /// \brief testSoftmax2d
    /// тестирование софтмакс в условиях двумерной матрицы
    void testSoftmax2d();
    ///
    /// \brief testSoftmax2d
    /// тестирование софтмакс в условиях трехмерной матрицы
    void testSoftmax3d();
    ///
    /// \brief testSigmoidMatrix2d
    /// тестирование сигмоидной функции в условиях двумерной матрицы
    void testSigmoidMatrix2d();
    ///
    /// \brief testSigmoidMatrix3d
    /// тестирование сигмоидной функции в условиях трехмерной матрицы
    void testSigmoidMatrix3d();
    ///
    /// \brief testDSigmoidMatrix2d
    /// тестирование производной от сигмоидной функции на 2д матрице
    void testDSigmoidMatrix2d();
    ///
    /// \brief testDSigmoidMatrix3d
    /// тестирование производной от сигмоидной функции на 3д матрице
    void testDSigmoidMatrix3d();
    ///
    /// \brief testTanhMatrix2d
    /// тестирование гиперболической тангенсовой функции на 2д матрице
    void testTanhMatrix2d();
    ///
    /// \brief testTanhMatrix3d
    /// тестирование гиперболической тангенсовой функции на 3д матрице
    void testTanhMatrix3d();
    ///
    /// \brief testDTanhMatrix2d
    /// тестирование производной от гиперболической функции на 2д матрице
    void testDTanhMatrix2d();
    ///
    /// \brief testDTanhMatrix3d
    /// тестирование производной от гиперболической функции на 3д матрице
    void testDTanhMatrix3d();
};

void TestActivationFunctions::testSoftmax()
{
    // инициализация
    Matrix2d<double> init{{5, 3, 2}};
    // итоговый и ожидаемый результаты
    Matrix2d<double> currentResult(ActivationFunctions<double>::softmax(&init)
                                       ->floorM(3)->data());
    Matrix2d<double> properResult{{0.843, 0.114, 0.042}};

    QCOMPARE(currentResult.data(), properResult.data());
}

void TestActivationFunctions::testSoftmax2d()
{
    Matrix2d<double> init{{5, 3, 2},
                          {2, 3, 1},
                          {6, 1, 8}};
    // итоговый и ожидаемый результаты
    Matrix2d<double> currentResult(
        ActivationFunctions<double>::softmax(&init)
            ->floorM(5)->data()
    );
    Matrix2d<double> properResult{{0.84379, 0.11419, 0.04201},
                                  {0.24472, 0.66524, 0.09003},
                                  {0.1191, 0.0008, 0.88009}};

    QCOMPARE(currentResult.data(), properResult.data());
}

void TestActivationFunctions::testSoftmax3d()
{
    // инициализация
    Matrix3d<double> init {{{5,3,2}, {2,3,1}, {6,1,8}},
                          {{8,2,1}, {5,6,1}, {2,2,8}}};
    // результаты
    Matrix3d<double> resultMatrix(
        ActivationFunctions<double>::softmax(&init)
            ->floorM(5)->data()
    );
    Matrix3d<double> properMatrix{{{0.84379,0.11419,0.04201},
                                   {0.24472,0.66524,0.09003},
                                   {0.1191,0.0008,0.88009}},
                                 {{0.99662,0.00247,0.0009},
                                   {0.26762,0.72747,0.0049},
                                   {0.00246,0.00246,0.99506}}};

    QCOMPARE(resultMatrix == properMatrix, true);
}

void TestActivationFunctions::testSigmoidMatrix2d()
{
    Matrix2d<double> init{{1, 3, 2},
                          {3, 2, 2},
                          {2, 2, 8}};
    // итоговый и ожидаемый результаты
    Matrix2d<double> currentResult(
        ActivationFunctions<double>::sigmoid(&init)
            ->floorM(5)->data()
        );
    Matrix2d<double> properResult{{0.73105,0.95257,0.88079},
                                  {0.95257,0.88079,0.88079},
                                  {0.88079,0.88079,0.99966}};

    init.print();
    currentResult.print();

    QCOMPARE(currentResult.data(), properResult.data());
}

void TestActivationFunctions::testSigmoidMatrix3d()
{
    // инициализация
    Matrix3d<double> init {{{5,3,2}, {2,3,1}, {6,1,8}},
                          {{8,2,1}, {5,6,1}, {2,2,8}}};
    // результаты
    Matrix3d<double> resultMatrix(
        ActivationFunctions<double>::sigmoid(&init)
            ->floorM(6)->data()
        );
    Matrix3d<double> properMatrix{{{0.993307,0.952574,0.880797},
                                   {0.880797,0.952574,0.731058},
                                   {0.997527,0.731058,0.999664}},
                                  {{0.999664,0.880797,0.731058},
                                   {0.993307,0.997527,0.731058},
                                   {0.880797,0.880797,0.999664}}};

    QCOMPARE(resultMatrix == properMatrix, true);
}

void TestActivationFunctions::testDSigmoidMatrix2d()
{
    Matrix2d<double> init{{7.7, 9.8, 2.2},
                          {6.6, 4.4, 5.5},
                          {7.7, 5.5, 3.3}};
    // итоговый и ожидаемый результаты
    Matrix2d<double> currentResult(
        ActivationFunctions<double>::dsigmoid(&init)
            ->floorM(5)->data()
        );
    Matrix2d<double> properResult{{0.00045,0.00005,0.08980},
                                  {0.00135,0.01198,0.00405},
                                  {0.00045,0.00405,0.03430}};

    QCOMPARE(currentResult.data(), properResult.data());
}

void TestActivationFunctions::testDSigmoidMatrix3d()
{
    // инициализация
    Matrix3d<double> init {{{5,3,2}, {2,3,1}},
                          {{8,2,1}, {5,6,1}}};
    // результаты
    Matrix3d<double> resultMatrix(
        ActivationFunctions<double>::dsigmoid(&init)
            ->floorM(6)->data()
        );
    Matrix3d<double> properMatrix{{{0.006648,0.045176,0.104993},
                                   {0.104993,0.045176,0.196611}},
                                  {{0.000335,0.104993,0.196611},
                                   {0.006648,0.002466,0.196611}}};

    QCOMPARE(resultMatrix == properMatrix, true);
}

void TestActivationFunctions::testTanhMatrix2d()
{
    Matrix2d<double> init{{7, 9, 2},
                          {6, 4, 5},
                          {7, 5, 3}};
    // итоговый и ожидаемый результаты
    Matrix2d<double> currentResult(
        ActivationFunctions<double>::tanh(&init)
            ->floorM(6)->data()
        );
    Matrix2d<double> properResult{{0.999998,0.999999,0.964027},
                                  {0.999987,0.999329,0.999909},
                                  {0.999998,0.999909,0.995054}};

    QCOMPARE(currentResult.data(), properResult.data());
}

void TestActivationFunctions::testTanhMatrix3d()
{
    // инициализация
    Matrix3d<double> init {{{5,3,2}, {2,3,1}},
                          {{8,2,1}, {5,6,1}}};
    // результаты
    Matrix3d<double> resultMatrix(
        ActivationFunctions<double>::tanh(&init)
            ->floorM(6)->data()
        );
    Matrix3d<double> properMatrix{{{0.999909,0.995054,0.964027},
                                   {0.964027,0.995054,0.761594}},
                                  {{0.999999,0.964027,0.761594},
                                   {0.999909,0.999987,0.761594}}};

    QCOMPARE(resultMatrix == properMatrix, true);
}

void TestActivationFunctions::testDTanhMatrix2d()
{
    Matrix2d<double> init{{7.5, 9.1, 2.2},
                          {6.2, 4.7, 5.55},
                          {7.77, 5.5, 3.33}};
    // итоговый и ожидаемый результаты
    Matrix2d<double> currentResult(
        ActivationFunctions<double>::dtanh(&init)->data()
        );
    Matrix2d<double> properResult{{1.22360853e-06,4.98730099e-08,4.79253442e-02},
                                  {1.64742191e-05,3.30841523e-04,6.04474683e-05},
                                  {7.13055916e-07,6.68045716e-05,5.11147998e-03}};

    QCOMPARE(currentResult.compareDoubles(properResult, 1e-10), true);
}

void TestActivationFunctions::testDTanhMatrix3d()
{
    // инициализация
    Matrix3d<double> init {{{5,3,2}, {2,3,1}},
                          {{8,2,1}, {5,6,1}}};
    // результаты
    Matrix3d<double> resultMatrix(
        ActivationFunctions<double>::dtanh(&init)->data()
        );
    Matrix3d<double> properMatrix{{{1.81583231e-04,9.86603717e-03,7.06508249e-02},
                                   {7.06508249e-02,9.86603717e-03,4.19974342e-01}},
                                  {{4.50140598e-07,7.06508249e-02,4.19974342e-01},
                                   {1.81583231e-04,2.45765474e-05,4.19974342e-01}}};

    QCOMPARE(resultMatrix.compareDoubles(properMatrix, 1e-9), true);
}

QTEST_MAIN(TestActivationFunctions)
#include "testactivationfunctions.moc"
