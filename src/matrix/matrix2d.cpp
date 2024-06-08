#include "matrix2d.h"

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
vector<vector<T>> Matrix2d<T>::dataToVector() const
{
    return _data;
}

template<typename T>
bool Matrix2d<T>::operator==(Matrix2d<T> &other)
{
    return this->data() == other.data();
}

template<typename T>
bool Matrix2d<T>::operator!=(Matrix2d<T> &other)
{
    return this->data() != other.data();
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
vector<int> Matrix2d<T>::sizes() const
{
    try {
        return vector<int>{_data.size(), _data[0].size()};
    } catch (...) {
        throw MatrixException(
            QString("\nMatrix exception \n[%1]\n")
                .arg("Trying to use uninitialized matrix")
        );
    }
}

template<typename T>
bool Matrix2d<T>::sameShape(const IMatrix<T> *other)
{
    try {
        Matrix2d<T> *otherMatrix = (Matrix2d<T>*)(other);
        return sizes() == otherMatrix->sizes();
    } catch (...) {
        throw MatrixException(
            QString("\nMatrix exception \n[%1]\n")
                .arg("Attempt to compare matrices with different dimensions (2d && 3d)")
        );
    }
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::addition(const IMatrix<T> *other)
{
    // проверки
    try {
        if (!this->sameShape(other)) {
            throw MatrixException(
                QString("\nMatrix exception \n[%1]\n")
                    .arg("Impossible to find matrix addition, the sizes do not match.")
            );
        }
    // если поймали исключение при выполнении 'this->sameShape(other)'
    } catch (const MatrixException &e) {
        throw e;
    }
    // подготовка
    vector<vector<T>> otherMatrixData = dataToVector(other);
    vector<vector<T>> resultData;
    // создание и заполнение результирующей матрицы
    for (int rowI = 0; rowI < _data.size(); ++rowI) {
        resultData.push_back(vector<T>());
        for (int colI = 0; colI < _data[0].size(); ++colI) {
            resultData[rowI].push_back(
                _data[rowI][colI] + otherMatrixData[rowI][colI]
            );
        }
    }
    return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T> > Matrix2d<T>::addition(T num)
{
    // подготовка
    vector<vector<T>> resultData;
    // создание и заполнение результирующей матрицы
    for (int rowI = 0; rowI < _data.size(); ++rowI) {
        resultData.push_back(vector<T>());
        for (int colI = 0; colI < _data[0].size(); ++colI) {
            resultData[rowI].push_back(
                _data[rowI][colI] + num
            );
        }
    }
    return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::subtraction(const IMatrix<T> *other)
{
    // проверки
    try {
        if (!this->sameShape(other)) {
            throw MatrixException(
                QString("\nMatrix subtraction exception \n[%1]\n")
                    .arg("Impossible to find matrix subtraction, the sizes do not match.")
                );
        }
        // если поймали исключение при выполнении 'this->sameShape(other)'
    } catch (const MatrixException &e) {
        throw e;
    }
    // подготовка
    vector<vector<T>> otherMatrixData = dataToVector(other);
    vector<vector<T>> resultData;
    // создание и заполнение результирующей матрицы
    for (int rowI = 0; rowI < _data.size(); ++rowI) {
        resultData.push_back(vector<T>());
        for (int colI = 0; colI < _data[0].size(); ++colI) {
            resultData[rowI].push_back(
                _data[rowI][colI] - otherMatrixData[rowI][colI]
            );
        }
    }
    return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::subtraction(T num, bool reverseOrder)
{
    // подготовка
    vector<vector<T>> resultData;
    // создание и заполнение результирующей матрицы
    for (int rowI = 0; rowI < _data.size(); ++rowI) {
        resultData.push_back(vector<T>());
        for (int colI = 0; colI < _data[0].size(); ++colI) {
            T stepValue = reverseOrder ? num - _data[rowI][colI]
                                       : _data[rowI][colI] - num;
            resultData[rowI].push_back(stepValue);
        }
    }
    return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::simplifiedMult(const IMatrix<T> *other)
{
    // проверки
    try {
        if (!this->sameShape(other)) {
            throw MatrixException(
                QString("\nMatrix exception \n[%1]\n")
                    .arg("Impossible to find matrix simplified multiplication, the sizes do not match.")
                );
        }
    // если поймали исключение при выполнении 'this->sameShape(other)'
    } catch (const MatrixException &e) {
        throw e;
    }
    // подготовка
    vector<vector<T>> otherMatrixData = dataToVector(other);
    vector<vector<T>> resultData;
    // создание и заполнение результирующей матрицы
    for (int rowI = 0; rowI < _data.size(); ++rowI) {
        resultData.push_back(vector<T>());
        for (int colI = 0; colI < _data[0].size(); ++colI) {
            resultData[rowI].push_back(
                _data[rowI][colI] * otherMatrixData[rowI][colI]
            );
        }
    }
    return unique_ptr<Matrix2d<T>>(new Matrix2d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix2d<T>::multiplication(T num)
{
    // подготовка
    vector<vector<T>> resultData;
    // создание и заполнение результирующей матрицы
    for (int rowI = 0; rowI < _data.size(); ++rowI) {
        resultData.push_back(vector<T>());
        for (int colI = 0; colI < _data[0].size(); ++colI) {
            resultData[rowI].push_back(
                _data[rowI][colI] * num
            );
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
unique_ptr<IMatrix<T>> Matrix2d<T>::softmaxM()
{
    // подготовка и заполнение результирующей матрицы
    vector<vector<T>> resultData;
    for (const vector<T> row : _data) {
        resultData.push_back(ActivationFunctions::softmax(row));
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
