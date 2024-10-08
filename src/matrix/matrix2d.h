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
    Matrix2d(const Matrix2d<T> &other);
    Matrix2d(const Matrix2d<T> *other);
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

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::doOperation(const IMatrix<T> *matrix)
{
    // проверки
    try {
        bool oneRow = false;
        if (!this->sameShape(matrix)) {
            if (matrix->sizes()[0] == 1) {
                oneRow = true;
            } else{
                throw MatrixException(
                    QString("\nMatrix operation exception \n[%1]\n")
                        .arg("Impossible to find matrix operation, the sizes do not match.")
                    );
            }
        }
        // подготовка
        vector<vector<T>> otherMatrixData = dataToVector(matrix);
        vector<vector<T>> resultData;
        // заполнение данных для результирующей матрицы
        for (int rowI = 0; rowI < _data.size(); ++rowI) {
            resultData.push_back(vector<T>());
            for (int i = 0; i < _data[0].size(); ++i) {
                resultData[rowI].push_back(
                    (*_operationPtr)(_data[rowI][i],
                                     otherMatrixData[oneRow ? 0 : rowI][i])
                    );
            }
        }

        return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
    } catch (const exception &e) {
        throw e;
    }
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::doOperation(const T num, bool reverseOrder)
{
    // подготовка
    vector<vector<T>> resultData;
    // заполнение данных для результирующей матрицы
    for (int rowI = 0; rowI < _data.size(); ++rowI) {
        resultData.push_back(vector<T>());
        for (int colI = 0; colI < _data[0].size(); ++colI) {
            T stepRes = reverseOrder ? (*_operationPtr)(num, _data[rowI][colI])
                                     : (*_operationPtr)(_data[rowI][colI], num);
            resultData[rowI].push_back(stepRes);
        }
    }

    return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::doOperation(T extraParam)
{
    // подготовка
    vector<vector<T>> resultData;
    // заполнение данных для результирующей матрицы
    for (int rowI = 0; rowI < _data.size(); ++rowI) {
        resultData.push_back(vector<T>());
        for (int i = 0; i < _data[0].size(); ++i) {
            resultData[rowI].push_back(
                (*_operationPtr)(_data[rowI][i], extraParam)
                );
        }
    }

    return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
}

template<typename T>
Matrix2d<T>::Matrix2d()
{
}

template<typename T>
Matrix2d<T>::Matrix2d(const Matrix2d<T> &other)
{
    _data = other._data;
    _operationPtr = other._operationPtr;
}

template<typename T>
Matrix2d<T>::Matrix2d(const Matrix2d<T> *other)
{
    _data = other->_data;
    _operationPtr = other->_operationPtr;
}

template<typename T>
Matrix2d<T>::Matrix2d(unique_ptr<IMatrix<T>> other)
{
    //cout << "unique_ptr matrix2d constructor" << endl;
    Matrix2d<T> *matrixOther = (Matrix2d<T>*)other.release();
    _data = matrixOther->_data;
    _operationPtr = matrixOther->_operationPtr;
    delete matrixOther;
}

template<typename T>
Matrix2d<T>::Matrix2d(QVariant data)
    : _data{data.value<vector<vector<T>>>()}
{
}

template<typename T>
Matrix2d<T>::Matrix2d(vector<vector<T>> data)
    : _data{data}
{
}

template<typename T>
Matrix2d<T>::Matrix2d(initializer_list<initializer_list<T>> list)
{
    for (initializer_list<T> row : list) {
        _data.push_back(row);
    }
}

template<typename T>
Matrix2d<T>::~Matrix2d()
{
    // cout << "matrix 2d destroyed" << endl;
}

template<typename T>
void Matrix2d<T>::print()
{
    cout << '[';
    for (const vector<T> row : _data) {
        cout << endl <<  '[';
        for (const T value : row) {
            cout << ' ' << value << ' ';
        }
        cout << ']';
    }
    cout << endl << ']';
}

template<typename T>
void Matrix2d<T>::setValue(int hIndex, int wIndex, const T value)
{
    try {
        _data[hIndex][wIndex] = value;
    } catch (...) {
        throw MatrixException(
            QString("\nMatrix set value exception \n[%1]\n")
                .arg("Incorrect height or width index")
            );
    }
}

template<typename T>
void Matrix2d<T>::setRow(const vector<T> row, int index)
{
    // проверки
    if (row.size() != _data[index].size()) {
        throw MatrixException(
            QString("\nMatrix set row exception \n[%1]\n")
                .arg("Trying to overwrite row with a new size")
            );
    }
    if (index >= _data.size() || index < 0) {
        throw MatrixException(
            QString("\nMatrix set row exception \n[%1]\n")
                .arg("Incorrect row index")
            );
    }

    _data[index] = row;
}

template<typename T>
void Matrix2d<T>::setOperation(OperationType opType)
{
    switch (opType) {
    case OperationType::SUM:
        _operationPtr = &Operations<T>::sum;
        break;
    case OperationType::SUB:
        _operationPtr = &Operations<T>::sub;
        break;
    case OperationType::MUL:
        _operationPtr = &Operations<T>::mul;
        break;
    case OperationType::DIV:
        _operationPtr = &Operations<T>::div;
        break;
    case OperationType::LOGM:
        _operationPtr = &Operations<T>::logM;
        break;
    case OperationType::EXPM:
        _operationPtr = &Operations<T>::expM;
        break;
    case OperationType::TANHM:
        _operationPtr = &Operations<T>::tanhM;
        break;
    case OperationType::SQRTM:
        _operationPtr = &Operations<T>::sqrtM;
        break;
    case OperationType::FLOORM:
        _operationPtr = &Operations<T>::floorM;
        break;
    }
}

template<typename T>
vector<vector<T>> Matrix2d<T>::dataToVector() const
{
    return _data;
}

template<typename T>
vector<vector<T>> Matrix2d<T>::dataToVector(const IMatrix<T> *matrix)
{
    Matrix2d<T> *otherMatrix = (Matrix2d<T>*)(matrix);
    return otherMatrix->dataToVector();
}

template<typename T>
void Matrix2d<T>::saveToFile(QString fileName)
{
    ofstream file;
    // пытаемся открыть файл
    file.open(fileName.toStdString());
    if (!file.is_open()) {
        throw MatrixException(
            QString("Catch matrix saving exception:\n[%1]\n")
                .arg("Failed to open file")
            );
    }
    // пишем информацию в файл
    for (const vector<T> &row : _data) {
        for (const T value : row) {
            file << value << " ";
        }
        file << endl;
    }

    file.close();
}

template<typename T>
void Matrix2d<T>::loadFromFile(QString fileName)
{
    // подготовка
    vector<vector<T>> resultData;
    ifstream file;
    // пытаемся открыть файл
    file.open(fileName.toStdString());
    if (!file.is_open()) {
        throw MatrixException(
            QString("Catch matrix loading exception:\n[%1]\n")
                .arg("Failed to open file")
            );
    }
    // построчно считываем данные
    string line;
    while (getline(file, line)) {
        vector<T> row;
        istringstream rowStream(line);
        T value;
        while (rowStream >> value) {
            row.push_back(value);
        }
        resultData.push_back(row);
    }
    // закрываем файл и обновляем данные
    file.close();
    _data = resultData;
}

template<typename T>
Matrix2d<T> Matrix2d<T>::zeroM(int height, int width)
{
    // подготовка
    vector<vector<T>> resultData;
    // заполнение данных для результирующей матрицы
    for (int h = 0; h < height; ++h) {
        resultData.push_back(vector<T>(width));
    }

    return Matrix2d(resultData);
}

template<typename T>
Matrix2d<T> Matrix2d<T>::randomNormal(T mean, T dispersion,
                                      int height, int width)
{
    // подготовка
    vector<vector<T>> resultData;
    // заполнение данных для результирующей матрицы
    for (int h = 0; h < height; ++h) {
        resultData.push_back(vector<T>());
        for (int w = 0; w < width; ++w) {
            resultData[h].push_back(
                Operations<T>::gaussianDistribution(mean, dispersion)
                );
        }
    }

    return Matrix2d(resultData);
}

template<typename T>
bool Matrix2d<T>::operator==(Matrix2d<T> &matrix)
{
    return this->data() == matrix.data();
}

template<typename T>
bool Matrix2d<T>::operator!=(Matrix2d<T> &matrix)
{
    return this->data() != matrix.data();
}

template<typename T>
Dimensions Matrix2d<T>::type() const
{
    return Dimensions::TWO;
}

template<typename T>
QVariant Matrix2d<T>::data() const
{
    return QVariant::fromValue(_data);
}

template<typename T>
vector<unsigned long long> Matrix2d<T>::sizes() const
{
    try {
        return vector<unsigned long long>{_data.size(), _data[0].size()};
    } catch (...) {
        throw MatrixException(
            QString("\nMatrix exception \n[%1]\n")
                .arg("Trying to use uninitialized matrix")
            );
    }
}

template<typename T>
bool Matrix2d<T>::sameShape(const IMatrix<T> *matrix)
{
    try {
        Matrix2d<T> *otherMatrix = (Matrix2d<T>*)(matrix);
        return sizes() == otherMatrix->sizes();
    } catch (...) {
        throw MatrixException(
            QString("\nMatrix exception \n[%1]\n")
                .arg("Attempt to compare matrices with different dimensions (2d && 3d)")
            );
    }
}

template<typename T>
bool Matrix2d<T>::compareDoubles(const Matrix2d<T> matrix, double epsilon)
{
    // пытаемся сравнить числа матриц, учитывая погрешность epsilon
    try {
        for (int rowI = 0; rowI < _data.size(); ++rowI) {
            for (int i = 0; i < _data[0].size(); ++i) {
                if (abs(_data[rowI][i]
                        - matrix.dataToVector()[rowI][i]) > epsilon) {
                    return false;
                }
            }
        }

        return true;
    } catch (...) {
        throw MatrixException(
            QString("\nMatrix compare exception \n[%1]\n")
                .arg("Impossible to compare the values ​​of matrices with different sizes")
            );
    }
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::addition(const IMatrix<T> *matrix)
{
    _operationPtr = &Operations<T>::sum;
    return doOperation(matrix);
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::addition(T num)
{
    _operationPtr = &Operations<T>::sum;
    return doOperation(num, false);
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::subtraction(const IMatrix<T> *matrix)
{
    _operationPtr = &Operations<T>::sub;
    return doOperation(matrix);
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::subtraction(T num, bool reverseOrder)
{
    _operationPtr = &Operations<T>::sub;
    return doOperation(num, reverseOrder);
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::simplifiedMult(const IMatrix<T> *matrix)
{
    _operationPtr = &Operations<T>::mul;
    return doOperation(matrix);
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::multiplication(T num)
{
    _operationPtr = &Operations<T>::mul;
    return doOperation(num, false);
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::multiplication(const IMatrix<T> *matrix)
{
    // подготовка
    vector<vector<T>> resultData;
    vector<vector<T>> otherMatrixData = dataToVector(matrix);
    int index = 0;
    // проверяем возможность перемножения матриц
    if (sizes()[1] != matrix->sizes()[0]) {
        throw MatrixException(
            QString("\nMatrix multiplication exception \n[%1]\n")
                .arg("Attempt multiply matrices with inappropriate sizes")
            );
    }
    // заполнение данных для результирующей матрицы
    for (const vector<T> rowA : _data) {
        resultData.push_back(vector<T>());
        int innerIndex = 0;
        // вычисление значений строки результирующей матрицы
        for (int indexB = 0; indexB < otherMatrixData[0].size(); ++indexB) {
            // вычисление значения ячейки
            T stepRes = 0;
            for (int indexA = 0; indexA < rowA.size(); ++indexA) {
                stepRes += otherMatrixData[indexA][innerIndex] * rowA[indexA];
            }
            resultData[index].push_back(stepRes);
            innerIndex++;
        }
        index++;
    }

    return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::simplifiedDiv(const IMatrix<T> *matrix)
{
    _operationPtr = &Operations<T>::div;
    return doOperation(matrix);
}

template<typename T>
unique_ptr<IMatrix<T> > Matrix2d<T>::dividing(T num, bool reverseOrder)
{
    _operationPtr = &Operations<T>::div;
    return doOperation(num, reverseOrder);
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::columnStack(const IMatrix<T> *matrix)
{
    // подготовка
    vector<vector<T>> otherMatrixData = dataToVector(matrix);
    vector<vector<T>> resultData;
    // заполнение данных для результирующей матрицы
    for (int rowI = 0; rowI < _data.size(); ++rowI) {
        resultData.push_back(vector<T>());
        for (int i = 0; i < _data[0].size(); ++i) {
            resultData[rowI].push_back(_data[rowI][i]);
        }
        for (int i = 0; i < otherMatrixData[0].size(); ++i) {
            resultData[rowI].push_back(otherMatrixData[rowI][i]);
        }
    }

    return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::rowsRepeat(const int count)
{
    // подготовка и заполнение данных для результирующей матрицы
    vector<vector<T>> resultData;
    for (int rowI = 0; rowI < _data.size(); ++rowI) {
        for (int repeatCount = 0; repeatCount < count; ++repeatCount) {
            resultData.push_back(_data[rowI]);
        }
    }

    return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::axisSum(const int axis)
{
    // проверки
    if (axis < 0 || axis >= 2) {
        throw MatrixException(
            QString("\nMatrix axis operation exception \n[%1]\n")
                .arg("Inaccessible axis selected")
            );
    }
    // подготовка
    vector<vector<T>> resultData;
    int rowIndex = 0;
    // заполняем данных для результирующей матрицы складывая строки
    if (axis == 0) {
        resultData.push_back(vector<T>(sizes()[1]));
        for (const vector<T> row : _data) {
            for (int i = 0; i < row.size(); ++i) {
                resultData[0][i] += row[i];
            }
        }
    }// заполнение данных для результирующей матрицы по колонкам
    else if (axis == 1) {
        for (const vector<T> row : _data) {
            resultData.push_back(vector<T>(1));
            for (int i = 0; i < row.size(); ++i) {
                resultData[rowIndex][0] += row[i];
            }
            rowIndex++;
        }
    }

    return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::axisMean(const int axis)
{
    // подготовка
    vector<vector<T>> resultData = dataToVector(axisSum(axis).get());
    unsigned long long divider = sizes()[axis];
    // заполнение данных для результирующей матрицы
    for (vector<T> &row : resultData) {
        for (int i = 0; i < row.size(); ++i) {
            row[i] /= divider;
        }
    }

    return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::slice(const vector<int> sliceIndices)
{
    // подготовка
    vector<vector<T>> resultData;
    int startH = sliceIndices[0] == -1 ? startH = 0
                                       : startH = sliceIndices[0];
    int endH = sliceIndices[1] == -1 ? endH = _data.size()
                                     : endH = sliceIndices[1];
    int startW = sliceIndices[2] == -1 ? startW = 0
                                       : startW = sliceIndices[2];
    int endW = sliceIndices[3] == -1 ? endW = _data[0].size()
                                     : endW = sliceIndices[3];
    int index = 0;
    // попытка заполнения данных для результирующей части матрицы
    try {
        for (int rowI = startH; rowI < endH; ++rowI) {
            resultData.push_back(vector<T>());
            for (int i = startW; i < endW; ++i) {
                resultData[index].push_back(_data[rowI][i]);
            }
            index++;
        }
    } catch (...) {
        throw MatrixException(
            QString("\nMatrix slice exception \n[%1]\n")
                .arg("Slice indices extend beyond the matrix")
            );
    }

    return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::transposition()
{
    // подготовка
    vector<vector<T>> resultData;
    int index = 0;
    // заполнение данных для результирующей матрицы
    for (int i = 0; i < _data[0].size(); ++i) {
        resultData.push_back(vector<T>());
    }
    for (const vector<T> row : _data) {
        for (const T value : row) {
            resultData[index++].push_back(value);
        }
        index = 0;
    }

    return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::floorM(T num)
{
    _operationPtr = &Operations<T>::floorM;
    return doOperation(num);
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::clipM(T leftBorder, T rightBorder)
{
    // подготовка
    vector<vector<T>> resultData;
    // заполнение данных для результирующей матрицы
    for (int rowI = 0; rowI < _data.size(); ++rowI) {
        resultData.push_back(vector<T>());
        for (int i = 0; i < _data[0].size(); ++i) {
            T oldValue = _data[rowI][i];
            T newValue;
            if (oldValue <= leftBorder) {
                newValue = leftBorder;
            } else if (oldValue >= rightBorder) {
                newValue = rightBorder;
            } else {
                newValue = oldValue;
            }
            resultData[rowI].push_back(newValue);
        }
    }

    return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::lognM()
{
    _operationPtr = &Operations<T>::logM;
    return doOperation();
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::expM()
{
    _operationPtr = &Operations<T>::expM;
    return doOperation();
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::tanhM()
{
    _operationPtr = &Operations<T>::tanhM;
    return doOperation();
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::sqrtM()
{
    _operationPtr = &Operations<T>::sqrtM;
    return doOperation();
}

template<typename T>
vector<T> Matrix2d<T>::toLine()
{
    // подготовка
    vector<T> resultLine;
    // заполнение вектора значений матрицы
    for (const vector<T> row : _data) {
        for (const T value : row) {
            resultLine.push_back(value);
        }
    }

    return resultLine;
}

template<typename T>
T Matrix2d<T>::totalSum()
{
    T result;
    for (const vector<T> row : _data) {
        for (const T value : row) {
            result += value;
        }
    }
    return result;
}

#endif // MATRIX2D_H
