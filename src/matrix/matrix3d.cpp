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
        // создание и заполнение результирующей матрицы
        for (int i = 0; i < _data.size(); ++i) {
            _data[i].setOperation(_opType); // перед выполнением нужно указать операцию!
            Matrix2d<T> stepMatrix(_data[i].doOperation(&otherMatrixData[i])->data());
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
    // создание и заполнение результирующей матрицы
    for (int i = 0; i < _data.size(); ++i) {
        _data[i].setOperation(_opType); // перед выполнением нужно указать операцию!
        Matrix2d<T> stepMatrix(_data[i].doOperation(num, reverseOrder)->data());
        resultData.push_back(stepMatrix);
    }
    return unique_ptr<Matrix3d<T>>(new Matrix3d(resultData));
}

template<typename T>
Matrix3d<T>::Matrix3d()
{
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
Matrix3d<T> Matrix3d<T>::zeroM(int depth, int height, int width)
{
    // подготовка
    vector<Matrix2d<T>> resultData;
    // создание и заполнение результирующей матрицы
    for (int d = 0; d < depth; ++d) {
        resultData.push_back(Matrix2d<T>::zeroM(height, width));
    }
    return Matrix3d(resultData);
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
void Matrix3d<T>::floorM(T num)
{
    for (Matrix2d<T> &matrix : _data) {
        matrix.floorM(num);
    }
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::clipM(T leftBorder, T rightBorder)
{
    // подготовка
    vector<Matrix2d<T>> resultData;
    // создание и заполнение результирующей матрицы
    for (Matrix2d<T> matrix : _data) {
        Matrix2d<T> stepMatrix(matrix.clipM(leftBorder, rightBorder)->data());
        resultData.push_back(stepMatrix);
    }
    return unique_ptr<Matrix3d<T>>(new Matrix3d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::lognM()
{
    // подготовка
    vector<Matrix2d<T>> resultData;
    // создание и заполнение результирующей матрицы
    for (Matrix2d<T> matrix : _data) {
        Matrix2d<T> stepMatrix((matrix.lognM())->data());
        resultData.push_back(stepMatrix);
    }
    return unique_ptr<Matrix3d<T>>(new Matrix3d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::expM()
{
    // подготовка
    vector<Matrix2d<T>> resultData;
    // создание и заполнение результирующей матрицы
    for (Matrix2d<T> matrix : _data) {
        Matrix2d<T> stepMatrix((matrix.expM())->data());
        resultData.push_back(stepMatrix);
    }
    return unique_ptr<Matrix3d<T>>(new Matrix3d(resultData));
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
