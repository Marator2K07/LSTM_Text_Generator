#ifndef MATRIX3D_H
#define MATRIX3D_H

#include "matrix2d.h"

///
/// \brief The Matrix3d class
/// частный случай - трехмерная матрица
/// важное замечание, данный класс является
/// надстройкой над классом Matrix2d
template<typename T>
class Matrix3d : public IMatrix<T>
{
private:
    vector<Matrix2d<T>> _data;
    OperationType _opType = OperationType::SUM;

public:
    Matrix3d();
    Matrix3d(unique_ptr<IMatrix<T>> other);
    Matrix3d(QVariant data);
    Matrix3d(vector<Matrix2d<T>> data);
    Matrix3d(initializer_list<initializer_list<initializer_list<T>>> list);

    ~Matrix3d();

public:
    void print();
    vector<Matrix2d<T>> dataToVector() const;
    static vector<Matrix2d<T>> dataToVector(const IMatrix<T> *matrix);
    ///
    /// \brief setValue установка нового значения для ячейки матрицы
    /// \param dIndex индекс матрицы
    /// \param hIndex индекс строки
    /// \param wIndex индекс значения в строке
    /// \param value новое значение ячейки
    void setValue(int dIndex, int hIndex, int wIndex, const T value);
    ///
    /// \brief zeroM создание новой матрицы, состоящей из нулей
    /// \param depth, width, height размеры новой матрицы
    /// \return нулевая матрица
    static Matrix3d<T> zeroM(int depth, int height, int width);
    ///
    /// \brief randomNormal создание 3д матрицы с размерами height и
    /// width заполненную случайными числами(по распределению гаусса)
    /// \param mean центральное значение - центр распределения
    /// \param dispersion разброс распределения
    /// \param depth глубина будущей матрицы
    /// \param height высота будущей матрицы
    /// \param width ширина будущей матрицы
    /// \return матрица со случайными значениями
    static Matrix3d<T> randomNormal(T mean, T dispersion,
                                    int depth, int height, int width);
    ///
    /// \brief rowsWithIndex все строки по индексу в виде 2д матрицы
    /// \param index индекс выбора строк
    /// \return результирующая матрица из собранных строк
    Matrix2d<T> rowsWithIndex(unsigned long long index);
    ///
    /// \brief setRowsWithIndex задание всем строкам с индексом из
    /// текущей матрицы значений строк из переданной матрицы
    /// \param rows переданная матрица
    /// \param index индекс для задания строк
    void setRowsWithIndex(const Matrix2d<T> rows, unsigned long long index);
    ///
    /// \brief compareDoubles сравнение значений матриц с вещественными значениями
    /// \param matrix матрица для сравнения
    /// \param epsilon допустимая погрешность
    /// \return флаг равенства значений матриц
    bool compareDoubles(const Matrix3d<T> matrix, double epsilon);

    bool operator==(Matrix3d<T> &matrix);

    // IMatrix interface
    Dimensions type() const override;
    QVariant data() const override;
    vector<unsigned long long> sizes() const override;
    bool sameShape(const IMatrix<T> *matrix) override;    
    unique_ptr<IMatrix<T>> doOperation(const IMatrix<T> *matrix) override;
    unique_ptr<IMatrix<T>> doOperation(const T num, bool reverseOrder) override;
    unique_ptr<IMatrix<T>> doOperation(T extraParam = 0) override;
    unique_ptr<IMatrix<T>> addition(const IMatrix<T> *matrix) override;
    unique_ptr<IMatrix<T>> addition(T num) override;
    unique_ptr<IMatrix<T>> subtraction(const IMatrix<T> *matrix) override;
    unique_ptr<IMatrix<T>> subtraction(T num, bool reverseOrder = false) override;
    unique_ptr<IMatrix<T>> simplifiedMult(const IMatrix<T> *matrix) override;
    unique_ptr<IMatrix<T>> multiplication(T num) override;
    unique_ptr<IMatrix<T>> multiplication(const IMatrix<T> *matrix) override;
    unique_ptr<IMatrix<T>> simplifiedDiv(const IMatrix<T> *matrix) override;
    unique_ptr<IMatrix<T>> dividing(T num, bool reverseOrder) override;
    unique_ptr<IMatrix<T>> columnStack(const IMatrix<T> *matrix) override;
    unique_ptr<IMatrix<T>> rowsRepeat(const int count) override;
    unique_ptr<IMatrix<T>> axisSum(const int axis) override;
    unique_ptr<IMatrix<T>> axisMean(const int axis) override;
    unique_ptr<IMatrix<T>> slice(const vector<int> sliceIndices) override;
    unique_ptr<IMatrix<T>> transposition() override;
    unique_ptr<IMatrix<T>> floorM(T num) override;
    unique_ptr<IMatrix<T>> clipM(T leftBorder, T rightBorder) override;
    unique_ptr<IMatrix<T>> lognM() override;
    unique_ptr<IMatrix<T>> expM() override;
    unique_ptr<IMatrix<T>> tanhM() override;
    unique_ptr<IMatrix<T>> sqrtM() override;
    vector<T> toLine() override;
    T totalSum() override;
    //

};

#endif // MATRIX3D_H
