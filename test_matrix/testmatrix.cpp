#include <QObject>
#include <QtTest/QtTest>

#include <matrix2d.h>
#include <matrix2d.cpp>

class TestMatrix: public QObject
{
    Q_OBJECT

private slots:
    ///
    /// \brief testMatrixSubtrNumDirectOrder
    /// проверка разности матрицы и
    /// числа в прямом порядке вычисления
    void testMatrixSubtrNumDirectOrder();
    ///
    /// \brief testMatrix2dMultNumber
    /// умножение матрицы на число
    void testMatrix2dMultNumber();
    ///
    /// \brief test1MatrixMultMatrix
    /// первое тестовое умножение матриц
    void test1MatrixMultMatrix();
    ///
    /// \brief test2MatrixMultMatrix
    /// усложенная версия умножения матриц
    void test2MatrixMultMatrix();
    ///
    /// \brief test3MatrixMultMatrix
    /// версия для плохого случая перемножения
    void test3MatrixMultMatrix();
    ///
    /// \brief testMatrixClip
    /// тест обрезки матрицы по границе
    /// в пределах: [leftBorder, 1-leftBorder]
    void testMatrixClip();
    ///
    /// \brief testMatrixLog
    /// тест нахождения логарифма
    /// каждого элемента матрицы
    void testMatrixLogn();
};

void TestMatrix::testMatrixSubtrNumDirectOrder()
{
    vector<vector<double>> matrix {{1,2,3},
                                   {7,3,5},
                                   {9,3,1}};
    vector<vector<double>> resultMatrix
        = Matrix2d<double>::subtraction(matrix, 2);
    vector<vector<double>> properMatrix {{-1,0,1},
                                         {5,1,3},
                                         {7,1,-1}};
    QCOMPARE(resultMatrix, properMatrix);
}

void TestMatrix::testMatrix2dMultNumber()
{
    vector<vector<double>> matrix {{1,2,3},
                                   {7,3,5},
                                   {9,3,1}};
    vector<vector<double>> resultMatrix
        = Matrix2d<double>::multiplication(matrix, -2);
    vector<vector<double>> properMatrix {{-2,-4,-6},
                                         {-14,-6,-10},
                                         {-18,-6,-2}};
    QCOMPARE(resultMatrix, properMatrix);
}

void TestMatrix::test1MatrixMultMatrix()
{
    vector<vector<double>> matrixA {{1,2,3},
                                    {3,4,5},
                                    {6,8,2}};
    vector<vector<double>> matrixB {{1,6,2},
                                    {3,2,2},
                                    {2,2,8}};
    vector<vector<double>> resultMatrix
        = Matrix2d<double>::multiplication(matrixA, matrixB);

    vector<vector<double>> properMatrix {{13,16,30},
                                         {25,36,54},
                                         {34,56,44}};
    QCOMPARE(resultMatrix, properMatrix);
}

void TestMatrix::test2MatrixMultMatrix()
{
    vector<vector<double>> matrixA {{1,2},
                                    {3,4},
                                    {7,7},
                                    {9,3}};
    vector<vector<double>> matrixB {{1,6,2},
                                    {3,2,2}};
    vector<vector<double>> resultMatrix
        = Matrix2d<double>::multiplication(matrixA, matrixB);

    vector<vector<double>> properMatrix {{7,10,6},
                                         {15,26,14},
                                         {28,56,28},
                                         {18,60,24}};
    QCOMPARE(resultMatrix, properMatrix);
}

void TestMatrix::test3MatrixMultMatrix()
{
    vector<vector<double>> matrixA {{1},
                                    {3}};
    vector<vector<double>> matrixB {{1,6,2},
                                    {3,2,2}};
    vector<vector<double>> resultMatrix
        = Matrix2d<double>::multiplication(matrixA, matrixB);

    vector<vector<double>> properMatrix;
    QCOMPARE(resultMatrix, properMatrix);
}

void TestMatrix::testMatrixClip()
{
    vector<vector<double>> matrix {{1,0.42,0.22},
                                   {0.642,0.33,0}};
    double leftBorder = 1e-9;

    vector<vector<double>> resultMatrix
        = Matrix2d<double>::clip(matrix, leftBorder);

    vector<vector<double>> properMatrix {{1-(1e-9),0.42,0.22},
                                         {0.642,0.33,1e-9}};
    QCOMPARE(resultMatrix, properMatrix);
}

void TestMatrix::testMatrixLogn()
{
    vector<vector<double>> matrix {{0.33,0.12,0.777},
                                   {0.642,0.33,0.123}};

    vector<vector<double>> resultMatrix
        = Matrix2d<double>::logn(matrix);
    // округляем значения
    Matrix2d<double>::floorM(resultMatrix, 1000);

    vector<vector<double>> properMatrix {{-1.109,-2.121,-0.253},
                                         {-0.444,-1.109,-2.096}};
    QCOMPARE(resultMatrix, properMatrix);
}

QTEST_MAIN(TestMatrix)
#include "testmatrix.moc"
