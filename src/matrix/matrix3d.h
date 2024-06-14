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
    // указатель на операцию с матрицей
    unique_ptr<IMatrix<T>> (Matrix2d<T>::*_operationMatrPtr)(const IMatrix<T>*);
    // указатель на операцию с числом
    unique_ptr<IMatrix<T>> (Matrix2d<T>::*_operationNumPtr)(T, bool);

public:
    Matrix3d();
    Matrix3d(QVariant data);
    Matrix3d(vector<Matrix2d<T>> data);
    Matrix3d(initializer_list<initializer_list<initializer_list<T>>> list);

public:
    void print();
    vector<Matrix2d<T>> dataToVector() const;
    static vector<Matrix2d<T>> dataToVector(const IMatrix<T> *matrix);
    ///
    /// \brief zeroM создание новой матрицы, состоящей из нулей
    /// \param depth,width,height размеры новой матрицы
    /// \return нулевая матрица
    static Matrix3d<T> zeroM(int depth, int height, int width);
    bool operator==(Matrix3d<T> &matrix);

    // IMatrix interface
    Dimensions type() const override;
    QVariant data() const override;
    vector<unsigned long long> sizes() const override;
    bool sameShape(const IMatrix<T> *matrix) override;
    unique_ptr<IMatrix<T>> doOperation(const IMatrix<T> *matrix) override;
    unique_ptr<IMatrix<T>> doOperation(const T num, bool reverseOrder) override;
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

#endif // MATRIX3D_H
