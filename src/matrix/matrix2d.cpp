#include "matrix2d.h"

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::doOperation(const IMatrix<T> *matrix)
{
    // проверки
    try {
        if (!this->sameShape(matrix)) {
            throw MatrixException(
                QString("\nMatrix exception \n[%1]\n")
                    .arg("Impossible to find matrix addition, the sizes do not match.")
                );
        }
        // если поймали исключение при выполнении 'this->sameShape(other)'
    } catch (const MatrixException &e) {
        throw e;
    }
    try {
        // подготовка
        vector<vector<T>> otherMatrixData = Matrix2d::dataToVector(matrix);
        vector<vector<T>> resultData;
        // создание и заполнение результирующей матрицы
        for (int rowI = 0; rowI < _data.size(); ++rowI) {
            resultData.push_back(vector<T>());
            for (int colI = 0; colI < _data[0].size(); ++colI) {
                resultData[rowI].push_back(
                    (*_operationPtr)(_data[rowI][colI],
                                     otherMatrixData[rowI][colI])
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
    // создание и заполнение результирующей матрицы
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
    // создание и заполнение результирующей матрицы
    for (int h = 0; h < height; ++h) {
        resultData.push_back(vector<T>());
        for (int w = 0; w < width; ++w) {
            resultData[h].push_back(0);
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
    // проверка
    if (!sameShape(matrix)) {
        throw MatrixException(
            QString("\nMatrix column stack exception \n[%1]\n")
                .arg("Matrices not have same sizes to do operation")
            );
    }
    // подготовка
    vector<vector<T>> otherMatrixData = dataToVector(matrix);
    vector<vector<T>> resultData;
    // заполнение результирующей матрицы
    for (int rowI = 0; rowI < _data.size(); ++rowI) {
        resultData.push_back(vector<T>());
        for (int i = 0; i < _data[0].size(); ++i) {
            resultData[rowI].push_back(_data[rowI][i]);            
        }
        for (int i = 0; i < _data[0].size(); ++i) {
            resultData[rowI].push_back(otherMatrixData[rowI][i]);
        }
    }

    return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
}

template<typename T>
void Matrix2d<T>::floorM(T num)
{
    int multiplier = pow(10, num);
    for (vector<T> &row : _data) {
        for (T &value : row) {
            value = floor(value * multiplier) / multiplier;
        }
    }
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::clipM(T leftBorder, T rightBorder)
{
    // подготовка
    vector<vector<T>> resultData;
    int index = 0;
    // заполнение результирующей матрицы
    for (const vector<T> row : _data) {
        resultData.push_back(vector<T>());
        for (const T value : row) {
            T newValue;
            if (value <= leftBorder) {
                newValue = leftBorder;
            } else if (value >= rightBorder) {
                newValue = rightBorder;
            } else {
                newValue = value;
            }
            resultData[index].push_back(newValue);
        }
        index++;
    }
    return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::lognM()
{
    // подготовка
    vector<vector<T>> resultData;
    int index = 0;
    // заполнение результирующей матрицы
    for (const vector<T> row : _data) {
        resultData.push_back(vector<T>());
        for (const T value : row) {
            resultData[index].push_back(log(value));
        }
        index++;
    }
    return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::expM()
{
    // подготовка
    vector<vector<T>> resultData;
    int index = 0;
    // заполнение результирующей матрицы
    for (const vector<T> row : _data) {
        resultData.push_back(vector<T>());
        for (const T value : row) {
            resultData[index].push_back(exp(value));
        }
        index++;
    }
    return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::tanhM()
{
    // подготовка
    vector<vector<T>> resultData;
    int index = 0;
    // заполнение результирующей матрицы
    for (const vector<T> row : _data) {
        resultData.push_back(vector<T>());
        for (const T value : row) {
            resultData[index].push_back(tanh(value));
        }
        index++;
    }
    return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
}

template<typename T>
T Matrix2d<T>::totalSum()
{
    T result;
    // заполнение результирующей матрицы
    for (const vector<T> row : _data) {
        for (const T value : row) {
            result += value;
        }
    }
    return result;
}
