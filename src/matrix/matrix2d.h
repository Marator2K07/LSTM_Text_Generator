#ifndef MATRIX2D_H
#define MATRIX2D_H

#include "imatrix.h"

///
/// \brief The Matrix2d class
/// частный случай - двумерная матрица
template<typename T>
class Matrix2d : public IMatrix<T>
{
private:
    vector<vector<T>> _data;
    T (*_operationPtr)(T, T) = &Operations<T>::sum; // указатель на операцию

public:
    Matrix2d();
    Matrix2d(QVariant data);
    Matrix2d(vector<vector<T>> data);
    Matrix2d(initializer_list<initializer_list<T>> list);

public:
    void print();
    vector<vector<T>> dataToVector() const;
    static vector<vector<T>> dataToVector(const IMatrix<T> *matrix);
    ///
    /// \brief setValue задание значения для ячейки
    /// \param hIndex индекс строки
    /// \param wIndex индекс значения в строке
    /// \param value новое значение ячейки
    void setValue(int hIndex, int wIndex, T value);
    ///
    /// \brief setOperation обновление типа операции извне,
    /// например, при использовании трехмерной матрицей
    /// \param opType передаваемый тип операции
    void setOperation(OperationType opType);    
    ///
    /// \brief zeroM создание новой матрицы, состоящей из нулей
    /// \param width,height размеры новой матрицы
    /// \return нулевая матрица
    static Matrix2d<T> zeroM(int height, int width);
    ///
    /// \brief randomNormal создание матрицы с размерами height и
    /// width заполненную случайными числами(по распределению гаусса)
    /// \param mean центральное значение - центр распределения
    /// \param dispersion разброс распределения
    /// \param height высота будущей матрицы
    /// \param width ширина будущей матрицы
    /// \return матрица со случайными значениями
    static Matrix2d<T> randomNormal(T mean, T dispersion,
                                    int height, int width);

    bool operator==(Matrix2d<T> &matrix);
    bool operator!=(Matrix2d<T> &matrix);

    // IMatrix interface
    Dimensions type() const override;
    QVariant data() const override;
    vector<unsigned long long> sizes() const override;
    bool sameShape(const IMatrix<T> *matrix) override;
    bool compareDoubles(const IMatrix<T> *matrix, double epsilon) override;
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
    unique_ptr<IMatrix<T>> axisSumMatrix(const int axis) override;
    unique_ptr<IMatrix<T>> transposition() override;
    unique_ptr<IMatrix<T>> floorM(T num) override;
    unique_ptr<IMatrix<T>> clipM(T leftBorder, T rightBorder) override;
    unique_ptr<IMatrix<T>> lognM() override;
    unique_ptr<IMatrix<T>> expM() override;
    unique_ptr<IMatrix<T>> tanhM() override;
    T totalSum() override;
    //

};

#endif // MATRIX2D_H
