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

public:
    Matrix3d();
    Matrix3d(QVariant data);
    Matrix3d(vector<Matrix2d<T>> data);
    Matrix3d(initializer_list<initializer_list<initializer_list<T>>> list);

public:
    void print();
    vector<Matrix2d<T>> dataToVector(const IMatrix<T> *other);
    ///
    /// \brief zeroM создание новой матрицы, состоящей из нулей
    /// \param depth,width,height размеры новой матрицы
    /// \return нулевая матрица
    static unique_ptr<Matrix3d<T>> zeroM(int depth, int width, int height);
    bool operator==(Matrix3d<T> &other);

    // IMatrix interface
    Dimensions type() const override;
    QVariant data() const override;
    vector<int> sizes() const override;
    bool sameShape(const IMatrix<T> *other) override;
    unique_ptr<IMatrix<T>> addition(const IMatrix<T> *other) override;
    unique_ptr<IMatrix<T>> addition(T num) override;
    unique_ptr<IMatrix<T>> subtraction(const IMatrix<T> *other) override;
    unique_ptr<IMatrix<T>> subtraction(T num, bool reverseOrder = false) override;
    unique_ptr<IMatrix<T>> simplifiedMult(const IMatrix<T> *other) override;
    unique_ptr<IMatrix<T>> multiplication(T num) override;
    void floorM(T num) override;
    unique_ptr<IMatrix<T>> clipM(T leftBorder, T rightBorder) override;
    unique_ptr<IMatrix<T>> lognM() override;
    unique_ptr<IMatrix<T>> softmaxM() override;
    T totalSum() override;

};

#endif // MATRIX3D_H
