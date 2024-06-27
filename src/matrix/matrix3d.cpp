#include "matrix3d.h"

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::doOperation(const IMatrix<T> *matrix)
{
    // проверки
    try {
        if (!this->sameShape(matrix)) {
            throw MatrixException(
                QString("\nMatrix exception \n[%1]\n")
                    .arg("Impossible to find matrix addition, the sizes do not match.")
                );
        }
        // если поймали исключение при выполнении 'this->sameShape(matrix)'
    } catch (const MatrixException &e) {
        throw e;
    }
    try {
        // подготовка
        vector<Matrix2d<T>> otherMatrixData = dataToVector(matrix);
        vector<Matrix2d<T>> resultData;
        // заполнение данных для результирующей матрицы
        for (int i = 0; i < _data.size(); ++i) {
            _data[i].setOperation(_opType); // перед выполнением нужно указать операцию!
            Matrix2d<T> stepMatrix(_data[i].doOperation(&otherMatrixData[i]));
            resultData.push_back(stepMatrix);
        }

        return unique_ptr<Matrix3d<T>>(new Matrix3d(resultData));
    } catch (const exception &e) {
        throw e;
    }
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::doOperation(const T num, bool reverseOrder)
{
    // подготовка
    vector<Matrix2d<T>> resultData;
    // заполнение данных для результирующей матрицы
    for (int i = 0; i < _data.size(); ++i) {
        _data[i].setOperation(_opType); // перед выполнением нужно указать операцию!
        Matrix2d<T> stepMatrix(_data[i].doOperation(num, reverseOrder));
        resultData.push_back(stepMatrix);
    }
    return unique_ptr<Matrix3d<T>>(new Matrix3d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::doOperation(T extraParam)
{
    // подготовка
    vector<Matrix2d<T>> resultData;
    // заполнение данных для результирующей матрицы
    for (int i = 0; i < _data.size(); ++i) {
        _data[i].setOperation(_opType); // перед выполнением нужно указать операцию!
        Matrix2d<T> stepMatrix(_data[i].doOperation(extraParam));
        resultData.push_back(stepMatrix);
    }
    return unique_ptr<Matrix3d<T>>(new Matrix3d(resultData));
}

template<typename T>
Matrix3d<T>::Matrix3d()
{
}

template<typename T>
Matrix3d<T>::Matrix3d(unique_ptr<IMatrix<T> > other)
{
    //cout << "unique_ptr matrix3d constructor" << endl;
    Matrix3d<T> *matrixOther = (Matrix3d<T>*)other.release();
    _data = matrixOther->_data;
    _opType = matrixOther->_opType;
    delete matrixOther;
}

template<typename T>
Matrix3d<T>::Matrix3d(QVariant data)
    : _data{data.value<vector<Matrix2d<T>>>()}
{
}

template<typename T>
Matrix3d<T>::Matrix3d(vector<Matrix2d<T>> data)
    : _data{data}
{
}

template<typename T>
Matrix3d<T>::Matrix3d(initializer_list<initializer_list<initializer_list<T>>> list)
{
    for (initializer_list<initializer_list<T>> matrix : list) {
        _data.push_back(Matrix2d(matrix));
    }
}

template<typename T>
Matrix3d<T>::~Matrix3d()
{
    // cout << "matrix 3d destroyed" << endl;
}

template<typename T>
void Matrix3d<T>::print()
{
    for (Matrix2d<T> matrix : _data) {
        matrix.print();
    }
}

template<typename T>
vector<Matrix2d<T>> Matrix3d<T>::dataToVector() const
{
    return _data;
}

template<typename T>
vector<Matrix2d<T>> Matrix3d<T>::dataToVector(const IMatrix<T> *matrix)
{
    Matrix3d<T> *otherMatrix = (Matrix3d<T>*)(matrix);
    QVariant otherMatrixAutoData = otherMatrix->data();

    return otherMatrixAutoData.value<vector<Matrix2d<T>>>();
}

template<typename T>
void Matrix3d<T>::setValue(int dIndex, int hIndex, int wIndex, const T value)
{
    try {
        _data[dIndex].setValue(hIndex, wIndex, value);
    } catch (...) {
        throw MatrixException(
            QString("\nMatrix set value exception \n[%1]\n")
                .arg("Incorrect value indices")
            );
    }
}

template<typename T>
Matrix3d<T> Matrix3d<T>::zeroM(int depth, int height, int width)
{
    // подготовка
    vector<Matrix2d<T>> resultData;
    // заполнение данных для результирующей матрицы
    for (int d = 0; d < depth; ++d) {
        resultData.push_back(Matrix2d<T>::zeroM(height, width));
    }
    return Matrix3d(resultData);
}

template<typename T>
Matrix3d<T> Matrix3d<T>::randomNormal(T mean, T dispersion,
                                      int depth, int height, int width)
{
    // подготовка
    vector<Matrix2d<T>> resultData;
    // заполнение данных для результирующей матрицы
    for (int d = 0; d < depth; ++d) {
        resultData.push_back(
            Matrix2d<T>::randomNormal(mean, dispersion, height, width)
            );
    }
    return Matrix3d(resultData);
}

template<typename T>
Matrix2d<T> Matrix3d<T>::rowsWithIndex(unsigned long long index)
{
    // подготавливаем с заполняем данные результирующей матрицы
    vector<vector<T>> resultData;
    for (unsigned long long matrixI = 0; matrixI < sizes()[0]; ++matrixI) {
        resultData.push_back(_data[matrixI].dataToVector()[index]);
    }

    return Matrix2d(resultData);
}

template<typename T>
void Matrix3d<T>::setRowsWithIndex(const Matrix2d<T> rows, unsigned long long index)
{
    // проверки
    if (sizes()[0] != rows.sizes()[0]) {
        throw MatrixException(
            QString("\nMatrix set rows exception \n[%1]\n")
                .arg("Number of rows does not match")
            );
    }
    if (index >= sizes()[1] || index < 0) {
        throw MatrixException(
            QString("\nMatrix set rows exception \n[%1]\n")
                .arg("Incorrect set rows index")
            );
    }
    // обновляем данные
    int i = 0;
    auto rowsMatrixData = rows.dataToVector();
    for (unsigned long long matrixI = 0; matrixI < sizes()[0]; ++matrixI) {
        _data[matrixI].setRow(rowsMatrixData[matrixI], index);
    }
}

template<typename T>
bool Matrix3d<T>::operator==(Matrix3d<T> &matrix)
{
    QVariant autoData = matrix.data();
    vector<Matrix2d<T>> otherMatrixData
        = autoData.value<vector<Matrix2d<T>>>();
    for (int i = 0; i < _data.size(); ++i) {
        if (_data[i] != otherMatrixData[i]) {
            return false;
        }
    }

    return true;
}

template<typename T>
Dimensions Matrix3d<T>::type() const
{
    return Dimensions::THREE;
}

template<typename T>
QVariant Matrix3d<T>::data() const
{
    return QVariant::fromValue(_data);
}

template<typename T>
vector<unsigned long long> Matrix3d<T>::sizes() const
{
    try {
        vector<unsigned long long> sizes{_data.size()};
        vector<unsigned long long> sizesInner{_data[0].sizes()};
        sizes.insert(sizes.end(), sizesInner.begin(), sizesInner.end());

        return sizes;
    } catch (...) {
        throw MatrixException(
            QString("\nMatrix exception \n[%1]\n")
                .arg("Trying to use uninitialized matrix")
        );
    }
}

template<typename T>
bool Matrix3d<T>::sameShape(const IMatrix<T> *matrix)
{
    try {
        Matrix3d<double> *otherMatrix = (Matrix3d<double>*)(matrix);
        return sizes() == otherMatrix->sizes();
    } catch (...) {
        throw MatrixException(
            QString("\nMatrix exception \n[%1]\n")
                .arg("Attempt to compare matrices with different dimensions (3d && 2d")
        );
    }
}

template<typename T>
bool Matrix3d<T>::compareDoubles(const IMatrix<T> *matrix, double epsilon)
{
    // подготовка
    Matrix3d<T> *otherMatrix = (Matrix3d<T>*)(matrix);
    // пытаемся сравнить числа матриц, учитывая погрешность epsilon
    try {
        for (int matrixI = 0; matrixI < _data.size(); ++matrixI) {
            if (!_data[matrixI].compareDoubles(&otherMatrix->dataToVector()[matrixI],
                                                epsilon)) {
                return false;
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
unique_ptr<IMatrix<T>> Matrix3d<T>::addition(const IMatrix<T> *matrix)
{
    _opType = OperationType::SUM;
    return doOperation(matrix);
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::addition(T num)
{
    _opType = OperationType::SUM;
    return doOperation(num, false);
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::subtraction(const IMatrix<T> *matrix)
{
    _opType = OperationType::SUB;
    return doOperation(matrix);
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::subtraction(T num, bool reverseOrder)
{
    _opType = OperationType::SUB;
    return doOperation(num, reverseOrder);
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::simplifiedMult(const IMatrix<T> *matrix)
{
    _opType = OperationType::MUL;
    return doOperation(matrix);
}

template<typename T>
unique_ptr<IMatrix<T> > Matrix3d<T>::multiplication(T num)
{
    _opType = OperationType::MUL;
    return doOperation(num, false);
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::multiplication(const IMatrix<T> *matrix)
{
    throw MatrixException(
        QString("\nMatrix multiplication exception \n[%1]\n")
            .arg("For 3d Matrices this type of operation is not allowed")
        );
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::simplifiedDiv(const IMatrix<T> *matrix)
{
    _opType = OperationType::DIV;
    return doOperation(matrix);
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::dividing(T num, bool reverseOrder)
{
    _opType = OperationType::DIV;
    return doOperation(num, reverseOrder);
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::columnStack(const IMatrix<T> *matrix)
{
    throw MatrixException(
        QString("\nMatrix column stack exception \n[%1]\n")
            .arg("For 3d Matrices this type of operation is not allowed")
        );
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::rowsRepeat(const int count)
{
    // подготовка и заполнение данных для результирующей матрицы
    vector<Matrix2d<T>> resultData;
    for (int matrixI = 0; matrixI < _data.size(); ++matrixI) {
        for (int repeatCount = 0; repeatCount < count; ++repeatCount) {
            resultData.push_back(
                Matrix2d<T>(_data[matrixI].rowsRepeat(1))
                );
        }
    }

    return unique_ptr<Matrix3d<T>>(new Matrix3d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::axisSum(const int axis)
{
    // проверки
    if (axis < 0 || axis >= 3) {
        throw MatrixException(
            QString("\nMatrix axis operation exception \n[%1]\n")
                .arg("Inaccessible axis selected")
            );
    }
    // подготовка
    vector<Matrix2d<T>> resultData;
    int rowIndex = 0;
    int index = 0;
    // заполнение данных матрицы по глубине
    if (axis == 0) {
        resultData.push_back(
            Matrix2d<T>::zeroM(sizes()[1], sizes()[2])
            );
        for (const Matrix2d<T> matrix : _data) {
            auto stepMatrixData = matrix.dataToVector();
            for (int rowI = 0; rowI < sizes()[1]; ++rowI) {
                for (int i = 0; i < sizes()[2]; ++i) {
                    resultData[0].setValue(
                        rowI, i, resultData[0].dataToVector()[rowI][i]
                                     + stepMatrixData[rowI][i]
                        );
                }
            }
        }
    }// заполнение данных матрицы по строкам или столбцам
    else if (axis == 1 || axis == 2) {
        for (Matrix2d<T> matrix : _data) {
            resultData.push_back(Matrix2d<T>(matrix.axisSum(axis-1)));
        }
    }

    return unique_ptr<Matrix3d<T>>(new Matrix3d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::axisMean(const int axis)
{
    // подготовка и заполнение данных для результирующей матрицы
    unsigned long long divider = sizes()[axis];
    vector<Matrix2d<T>> resultData = Matrix3d<T>::dataToVector(
            axisSum(axis)->dividing(divider).get()
        );

    return unique_ptr<Matrix3d<T>>(new Matrix3d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::slice(const vector<int> sliceIndices)
{
    throw MatrixException(
        QString("\nMatrix slice exception \n[%1]\n")
            .arg("For 3d Matrices this type of operation not implemented yet")
        );
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::transposition()
{
    // подготовка
    vector<Matrix2d<T>> resultData;
    int step = 0;
    int rowI = 0;
    int index = 0;
    // заполнение промежуточных данных для итоговой матрицы
    for (int i = 0; i < sizes()[2]; ++i) {
        Matrix2d<T> stepMatrix = Matrix2d<T>::zeroM(sizes()[0],
                                                    sizes()[1]);
        for (const Matrix2d<T> matrix : _data) {
            for (const vector<T> row : matrix.dataToVector()) {
                stepMatrix.setValue(rowI++, index, row[step]);
            }
            index++;
            rowI = 0;
        }
        step++;
        index = 0;
        resultData.push_back(stepMatrix);
    }
    // транспонируем матрицы по отдельности
    for (Matrix2d<T> matrix : resultData) {
        matrix = Matrix2d<T>(matrix.transposition());
    }

    return unique_ptr<Matrix3d<T>>(new Matrix3d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::floorM(T num)
{
    _opType = OperationType::FLOORM;
    return doOperation(num);
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::clipM(T leftBorder, T rightBorder)
{
    // подготовка
    vector<Matrix2d<T>> resultData;
    // заполнение данных для результирующей матрицы
    for (int i = 0; i < _data.size(); ++i) {
        _data[i].setOperation(_opType); // перед выполнением нужно указать операцию!
        Matrix2d<T> stepMatrix(_data[i].clipM(leftBorder, rightBorder));
        resultData.push_back(stepMatrix);
    }

    return unique_ptr<Matrix3d<T>>(new Matrix3d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::lognM()
{
    _opType = OperationType::LOGM;
    return doOperation();
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::expM()
{
    _opType = OperationType::EXPM;
    return doOperation();
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::tanhM()
{
    _opType = OperationType::TANHM;
    return doOperation();
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::sqrtM()
{
    _opType = OperationType::SQRTM;
    return doOperation();
}

template<typename T>
vector<T> Matrix3d<T>::toLine()
{
    // подготовка
    vector<T> resultLine;
    // заполнения вектора значений на основе
    // векторой значений каждой матрицы
    for (Matrix2d<T> matrix : _data) {
        vector<T> stepLine = matrix.toLine();
        resultLine.insert(resultLine.end(),
                          stepLine.begin(),
                          stepLine.end());
    }

    return resultLine;
}

template<typename T>
T Matrix3d<T>::totalSum()
{
    T result;
    for (Matrix2d<T> matrix : _data) {
        result += matrix.totalSum();
    }
    return result;
}
