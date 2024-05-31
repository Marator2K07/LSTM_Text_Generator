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

QTEST_MAIN(TestMatrix)
#include "testmatrix.moc"
