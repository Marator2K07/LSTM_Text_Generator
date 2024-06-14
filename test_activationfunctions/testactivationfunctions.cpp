#include <QObject>
#include <QtTest/QtTest>

#include "activationfunctions.h"
#include "activationfunctions.cpp"
#include "matrix2d.h"
#include "matrix2d.cpp"
#include "matrix3d.h"
#include "matrix3d.cpp"

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
};

void TestActivationFunctions::testSoftmax()
{
    // инициализация
    Matrix2d<double> init{{5, 3, 2}};
    // итоговый и ожидаемый результаты
    Matrix2d<double> currentResult(ActivationFunctions<double>::softmax(&init)->data());
    currentResult.floorM(3);
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
        ActivationFunctions<double>::softmax(&init)->data()
    );
    currentResult.floorM(5);
    Matrix2d<double> properResult{{0.84379, 0.11419, 0.04201},
                                  {0.24472, 0.66524, 0.09003},
                                  {0.1191, 0.0008, 0.88009}};

    QCOMPARE(currentResult.data(), properResult.data());
}
}

QTEST_MAIN(TestActivationFunctions)
#include "testactivationfunctions.moc"
