#include "matrix3d.h"

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
vector<Matrix2d<T>> Matrix3d<T>::dataToVector(const IMatrix<T> *other)
{
    Matrix3d<T> *otherMatrix = (Matrix3d<T>*)(other);
    QVariant otherMatrixAutoData = otherMatrix->data();
    return otherMatrixAutoData.value<vector<Matrix2d<T>>>();
}

template<typename T>
bool Matrix3d<T>::operator==(Matrix3d<T> &other)
{
    QVariant autoData = other.data();
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
QVariant Matrix3d<T>::data() const
{
    return QVariant::fromValue(_data);
}

template<typename T>
vector<int> Matrix3d<T>::sizes() const
{
    try {
        vector<int> sizes{_data.size()};
        vector<int> sizesInner{_data[0].sizes()};
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
bool Matrix3d<T>::sameShape(const IMatrix<T> *other)
{
    try {
        Matrix3d<double> *otherMatrix = (Matrix3d<double>*)(other);
        return sizes() == otherMatrix->sizes();
    } catch (...) {
        throw MatrixException(
            QString("\nMatrix exception \n[%1]\n")
                .arg("Attempt to compare matrices with different dimensions (3d && 2d")
        );
    }
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::addition(const IMatrix<T> *other)
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
    vector<Matrix2d<T>> otherMatrixData = dataToVector(other);
    vector<Matrix2d<T>> resultData;
    // создание и заполнение результирующей матрицы
    for (int i = 0; i < _data.size(); ++i) {
        Matrix2d<T> stepMatrix(_data[i].addition(&otherMatrixData[i])->data());
        resultData.push_back(stepMatrix);
    }
    return unique_ptr<Matrix3d<T>>(new Matrix3d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::addition(T num)
{
    // подготовка
    vector<Matrix2d<T>> resultData;
    // создание и заполнение результирующей матрицы
    for (int i = 0; i < _data.size(); ++i) {
        Matrix2d<T> stepMatrix(_data[i].addition(num)->data());
        resultData.push_back(stepMatrix);
    }
    return unique_ptr<Matrix3d<T>>(new Matrix3d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::subtraction(const IMatrix<T> *other)
{
    // проверки
    try {
        if (!this->sameShape(other)) {
            throw MatrixException(
                QString("\nMatrix exception \n[%1]\n")
                    .arg("Impossible to find matrix subtraction, the sizes do not match.")
            );
        }
        // если поймали исключение при выполнении 'this->sameShape(other)'
    } catch (const MatrixException &e) {
        throw e;
    }
    // подготовка
    vector<Matrix2d<T>> otherMatrixData = dataToVector(other);
    vector<Matrix2d<T>> resultData;
    // создание и заполнение результирующей матрицы
    for (int i = 0; i < _data.size(); ++i) {
        Matrix2d<T> stepMatrix(_data[i].subtraction(&otherMatrixData[i])->data());
        resultData.push_back(stepMatrix);
    }
    return unique_ptr<Matrix3d<T>>(new Matrix3d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::subtraction(T num, bool reverseOrder)
{
    // подготовка
    vector<Matrix2d<T>> resultData;
    // создание и заполнение результирующей матрицы
    for (int i = 0; i < _data.size(); ++i) {
        Matrix2d<T> stepMatrix(_data[i].subtraction(num, reverseOrder)->data());
        resultData.push_back(stepMatrix);
    }
    return unique_ptr<Matrix3d<T>>(new Matrix3d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T>> Matrix3d<T>::simplifiedMult(const IMatrix<T> *other)
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
    vector<Matrix2d<T>> otherMatrixData = dataToVector(other);
    vector<Matrix2d<T>> resultData;
    // создание и заполнение результирующей матрицы
    for (int i = 0; i < _data.size(); ++i) {
        Matrix2d<T> stepMatrix(_data[i].simplifiedMult(&otherMatrixData[i])->data());
        resultData.push_back(stepMatrix);
    }
    return unique_ptr<Matrix3d<T>>(new Matrix3d(resultData));
}

template<typename T>
unique_ptr<IMatrix<T> > Matrix3d<T>::multiplication(T num)
{
    // подготовка
    vector<Matrix2d<T>> resultData;
    // создание и заполнение результирующей матрицы
    for (int i = 0; i < _data.size(); ++i) {
        Matrix2d<T> stepMatrix(_data[i].multiplication(num)->data());
        resultData.push_back(stepMatrix);
    }
    return unique_ptr<Matrix3d<T>>(new Matrix3d(resultData));
}

template<typename T>
void Matrix3d<T>::floorM(T num)
{

}
