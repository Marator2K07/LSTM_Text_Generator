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

public:
    Matrix2d();
    Matrix2d(QVariant data);
    Matrix2d(vector<vector<T>> data);
    Matrix2d(initializer_list<initializer_list<T>> list);

public:
    void print();
    vector<vector<T>> dataToVector() const;
    bool operator==(Matrix2d<T> &other);
    bool operator!=(Matrix2d<T> &other);

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
    T totalSum() override;

};

#endif // MATRIX2D_H
