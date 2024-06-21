#include "matrix2d.h"

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
                    QString("\nMatrix exception \n[%1]\n")
                        .arg("Impossible to find matrix addition, the sizes do not match.")
                    );
            }
        }    
        // подготовка
        vector<vector<T>> otherMatrixData = Matrix2d::dataToVector(matrix);
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
void Matrix2d<T>::setValue(int hIndex, int wIndex, T value)
{
    _data[hIndex][wIndex] = value;
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
    case OperationType::CLIPM:
        _operationPtr = &Operations<T>::clipM;
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
    QVariant otherMatrixAutoData = otherMatrix->data();
    return otherMatrixAutoData.value<vector<vector<T>>>();
}

template<typename T>
Matrix2d<T> Matrix2d<T>::zeroM(int height, int width)
{
    // подготовка
    vector<vector<T>> resultData;
    // заполнение данных для результирующей матрицы
    for (int h = 0; h < height; ++h) {
        resultData.push_back(vector<T>());
        for (int w = 0; w < width; ++w) {
            resultData[h].push_back(0);
        }
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
bool Matrix2d<T>::compareDoubles(const IMatrix<T> *matrix, double epsilon)
{
    // подготовка
    Matrix2d<T> *otherMatrix = (Matrix2d<T>*)(matrix);
    // пытаемся сравнить числа матриц, учитывая погрешность epsilon
    try {
        for (int rowI = 0; rowI < _data.size(); ++rowI) {
            for (int i = 0; i < _data[0].size(); ++i) {
                if (abs(_data[rowI][i]
                        - otherMatrix->dataToVector()[rowI][i]) > epsilon) {
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
    // подготовка
    vector<vector<T>> resultData;
    int rowIndex = 0;
    // заполняем данных для результирующей матрицы складывая строки
    if (axis == 0) {
        resultData.push_back(vector<T>(sizes()[axis]+1));
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
    vector<vector<T>> resultData
        = Matrix2d<T>::dataToVector(axisSum(axis).get());
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
    _operationPtr = &Operations<T>::clipM;
    return doOperation(leftBorder);
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
