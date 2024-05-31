#include <QObject>
#include <QtTest/QtTest>

#include <matrix2d.h>
#include <matrix2d.cpp>

class TestMatrix: public QObject
{
    Q_OBJECT

private slots:
    ///
    /// \brief testMatrix2dMultNumber
    /// умножение матрицы на число
    void testMatrix2dMultNumber();
    ///
    /// \brief test1MatrixMultMatrix
    /// первое тестовое умножение матриц
    void test1MatrixMultMatrix();
};

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

QTEST_MAIN(TestMatrix)
#include "testmatrix.moc"
