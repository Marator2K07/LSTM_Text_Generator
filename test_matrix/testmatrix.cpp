#include <QObject>
#include <QtTest/QtTest>

#include <matrix2d.h>
#include <matrix2d.cpp>

class TestMatrix: public QObject
{
    Q_OBJECT

private slots:
    ///
    /// \brief testMatrixSameShape
    /// тест на полное соотвествие
    /// матриц по размерам
    void testMatrixSameShape();
    ///
    /// \brief testMatrixSubtrMatrix
    /// тест разности матриц
    void testMatrixSubtrMatrix();
    ///
    /// \brief testMatrixSubtrNumDirectOrder
    /// проверка разности матрицы и
    /// числа в прямом порядке вычисления
    void testMatrixSubtrNumDirectOrder();
    ///
    /// \brief testMatrixSubtrNumReverseOrder
    /// проверка разницы матрицы и числа
    /// при обратном порядке операндов
    void testMatrixSubtrNumReverseOrder();
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
    ///
    /// \brief testTotalMatrixSum
    /// тестирование общей суммы
    /// всех элементов матрицы
    void testTotalMatrixSum();
};

void TestMatrix::testMatrixSameShape()
{
    // инициализация
    vector<vector<double>> matrixA {{1,2,3},
                                    {4,7,7},
                                    {9,3,0}};
    vector<vector<double>> matrixB {{6,2,3},
                                    {2,2,0},
                                    {6,1,7}};
    vector<vector<double>> matrixC {{1,1,1},
                                    {2,2,2}};
    // итоговые результаты
    bool resultFlag1
        = Matrix2d<double>::sameShape(matrixA, matrixB);
    bool resultFlag2
        = Matrix2d<double>::sameShape(matrixA, matrixC);

    QCOMPARE(resultFlag1, true);
    QCOMPARE(resultFlag2, false);
}

void TestMatrix::testMatrixSubtrMatrix()
{
    // инициализация
    vector<vector<double>> matrixA {{1,2,3},
                                    {4,7,7},
                                    {9,3,0}};
    vector<vector<double>> matrixB {{6,2,3},
                                    {2,2,0},
                                    {6,1,7}};
    // итоговый и ожидаемый результаты
    vector<vector<double>> resultMatrix
        = Matrix2d<double>::subtraction(matrixA, matrixB);
    vector<vector<double>> properMatrix {{-5,0,0},
                                         {2,5,7},
                                         {3,2,-7}};

    QCOMPARE(resultMatrix, properMatrix);
}

void TestMatrix::testMatrixSubtrNumDirectOrder()
{
    // инициализация
    vector<vector<double>> matrix {{1,2,3},
                                   {7,3,5},
                                   {9,3,1}};
    // итоговый и ожидаемый результаты
    vector<vector<double>> resultMatrix
        = Matrix2d<double>::subtraction(matrix, 2);
    vector<vector<double>> properMatrix {{-1,0,1},
                                         {5,1,3},
                                         {7,1,-1}};

    QCOMPARE(resultMatrix, properMatrix);
}

void TestMatrix::testMatrixSubtrNumReverseOrder()
{
    // инициализация
    vector<vector<double>> matrix {{0.5,0.2,0.3},
                                   {0.7,0.3,0.5},
                                   {0.9,0.3,0.1}};
    // итоговый и ожидаемый результаты
    vector<vector<double>> resultMatrix
        = Matrix2d<double>::subtraction(matrix, 1, true);
    Matrix2d<double>::floorM(resultMatrix, 100); // округляем для сравнения
    vector<vector<double>> properMatrix {{0.5,0.8,0.7},
                                         {0.3,0.7,0.5},
                                         {0.09,0.7,0.9}};

    QCOMPARE(resultMatrix, properMatrix);
}

void TestMatrix::testMatrix2dMultNumber()
{
    // инициализация
    vector<vector<double>> matrix {{1,2,3},
                                   {7,3,5},
                                   {9,3,1}};
    // итоговый и ожидаемый результаты
    vector<vector<double>> resultMatrix
        = Matrix2d<double>::multiplication(matrix, -2);
    vector<vector<double>> properMatrix {{-2,-4,-6},
                                         {-14,-6,-10},
                                         {-18,-6,-2}};

    QCOMPARE(resultMatrix, properMatrix);
}

void TestMatrix::test1MatrixMultMatrix()
{
    // инициализация
    vector<vector<double>> matrixA {{1,2,3},
                                    {3,4,5},
                                    {6,8,2}};
    vector<vector<double>> matrixB {{1,6,2},
                                    {3,2,2},
                                    {2,2,8}};
    // итоговый и ожидаемый результаты
    vector<vector<double>> resultMatrix
        = Matrix2d<double>::multiplication(matrixA, matrixB);
    vector<vector<double>> properMatrix {{13,16,30},
                                         {25,36,54},
                                         {34,56,44}};

    QCOMPARE(resultMatrix, properMatrix);
}

void TestMatrix::test2MatrixMultMatrix()
{
    // инициализация
    vector<vector<double>> matrixA {{1,2},
                                    {3,4},
                                    {7,7},
                                    {9,3}};
    vector<vector<double>> matrixB {{1,6,2},
                                    {3,2,2}};
    // итоговый и ожидаемый результаты
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
    // инициализация
    vector<vector<double>> matrixA {{1},
                                    {3}};
    vector<vector<double>> matrixB {{1,6,2},
                                    {3,2,2}};
    // итоговый и ожидаемый результаты
    vector<vector<double>> resultMatrix
        = Matrix2d<double>::multiplication(matrixA, matrixB);
    vector<vector<double>> properMatrix;

    QCOMPARE(resultMatrix, properMatrix);
}

void TestMatrix::testMatrixClip()
{
    // инициализация
    vector<vector<double>> matrix {{1,0.42,0.22},
                                   {0.642,0.33,0}};
    double leftBorder = 1e-9;
    // итоговый и ожидаемый результаты
    vector<vector<double>> resultMatrix
        = Matrix2d<double>::clip(matrix, leftBorder);
    vector<vector<double>> properMatrix {{1-(1e-9),0.42,0.22},
                                         {0.642,0.33,1e-9}};

    QCOMPARE(resultMatrix, properMatrix);
}

void TestMatrix::testMatrixLogn()
{
    // инициализация
    vector<vector<double>> matrix {{0.33,0.12,0.777},
                                   {0.642,0.33,0.123}};
    // итоговый и ожидаемый результаты
    vector<vector<double>> resultMatrix
        = Matrix2d<double>::logn(matrix);    
    Matrix2d<double>::floorM(resultMatrix, 1000); // округляем для сравнения
    vector<vector<double>> properMatrix {{-1.109,-2.121,-0.253},
                                         {-0.444,-1.109,-2.096}};

    QCOMPARE(resultMatrix, properMatrix);
}

void TestMatrix::testTotalMatrixSum()
{
    // инициализация
    vector<vector<double>> matrix {{0.33,0.12,0.777},
                                   {0.642,0.33,0.123}};
    // итоговый и ожидаемый результаты
    double resultSum = Matrix2d<double>::totalSum(matrix);
    double properSum = 2.322;

    QCOMPARE(resultSum, properSum);
}

QTEST_MAIN(TestMatrix)
#include "testmatrix.moc"
