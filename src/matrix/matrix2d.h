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
    T (Matrix2d<T>::*_operationPtr)(T, T) = &sum; // указатель на операцию

private:
    T sum(T a, T b);
    T sub(T a, T b);
    T mul(T a, T b);

    // IMatrix interface
    unique_ptr<IMatrix<T>> doOperation(const IMatrix<T> *matrix) override;
    unique_ptr<IMatrix<T>> doOperation(const T num, bool reverseOrder) override;
    //

public:
    Matrix2d();
    Matrix2d(QVariant data);
    Matrix2d(vector<vector<T>> data);
    Matrix2d(initializer_list<initializer_list<T>> list);

public:
    void print();
    ///
    /// \brief setValue задание значения для ячейки
    /// \param hIndex индекс строки
    /// \param wIndex индекс значения в строке
    /// \param value новое значение ячейки
    void setValue(int hIndex, int wIndex, T value);
    vector<vector<T>> dataToVector() const;
    static vector<vector<T>> dataToVector(const IMatrix<T> *matrix);
    ///
    /// \brief zeroM создание новой матрицы, состоящей из нулей
    /// \param width,height размеры новой матрицы
    /// \return нулевая матрица
    static Matrix2d<T> zeroM(int height, int width);
    bool operator==(Matrix2d<T> &matrix);
    bool operator!=(Matrix2d<T> &matrix);

    // IMatrix interface
    Dimensions type() const override;
    QVariant data() const override;
    vector<unsigned long long> sizes() const override;
    bool sameShape(const IMatrix<T> *matrix) override;
    unique_ptr<IMatrix<T>> addition(const IMatrix<T> *matrix) override;
    unique_ptr<IMatrix<T>> addition(T num) override;
    unique_ptr<IMatrix<T>> subtraction(const IMatrix<T> *matrix) override;
    unique_ptr<IMatrix<T>> subtraction(T num, bool reverseOrder = false) override;
    unique_ptr<IMatrix<T>> simplifiedMult(const IMatrix<T> *matrix) override;
    unique_ptr<IMatrix<T>> multiplication(T num) override;
    void floorM(T num) override;
    unique_ptr<IMatrix<T>> clipM(T leftBorder, T rightBorder) override;
    unique_ptr<IMatrix<T>> lognM() override;
    T totalSum() override;
    //

};

#endif // MATRIX2D_H
