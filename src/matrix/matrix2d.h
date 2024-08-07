#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <QFile>
#include <iostream>
#include <fstream>
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
    Matrix2d(unique_ptr<IMatrix<T>> other);
    Matrix2d(QVariant data);
    Matrix2d(vector<vector<T>> data);
    Matrix2d(initializer_list<initializer_list<T>> list);

    ~Matrix2d();

public:
    void print();
    vector<vector<T>> dataToVector() const;
    static vector<vector<T>> dataToVector(const IMatrix<T> *matrix);
    ///
    /// \brief saveToFile сохранение информации 2д матрицы в файл
    /// \param fileName полное название файла
    void saveToFile(QString fileName);
    ///
    /// \brief loadFromFile выгрузка информации для 2д матрицы из файла
    /// \param fileName полное название файла
    void loadFromFile(QString fileName);
    ///
    /// \brief setValue задание значения для ячейки
    /// \param hIndex индекс строки
    /// \param wIndex индекс значения в строке
    /// \param value новое значение ячейки
    void setValue(int hIndex, int wIndex, const T value);
    ///
    /// \brief setRow сеттер для выбранной по индексу строки
    /// \param row новое значение строки
    /// \param index индекс для смены
    void setRow(const vector<T> row, int index);
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
    ///
    /// \brief compareDoubles сравнение значений матриц с вещественными значениями
    /// \param matrix матрица для сравнения
    /// \param epsilon допустимая погрешность
    /// \return флаг равенства значений матриц
    bool compareDoubles(const Matrix2d<T> matrix, double epsilon);

    bool operator==(Matrix2d<T> &matrix);
    bool operator!=(Matrix2d<T> &matrix);

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

#endif // MATRIX2D_H
