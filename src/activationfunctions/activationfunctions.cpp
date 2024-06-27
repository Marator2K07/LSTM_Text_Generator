#include "activationfunctions.h"
#include "matrix3d.h"

template<typename T>
vector<double> ActivationFunctions<T>::softmaxRow(vector<T> row)
{
    // сначала находим общий знаменатель
    double denominator = 0;
    for (const double value : row) {
        denominator += exp(value);
    }
    // следующим проходом составляем обработанный вектор
    vector<double> result;
    for (const double value : row) {
        result.push_back(exp(value)/denominator);
    }

    return result;
}

template<typename T>
unique_ptr<IMatrix<double>>
ActivationFunctions<T>::sigmoid(IMatrix<T> *matrix)
{
    IMatrix<double> *resMatrix
        = matrix->multiplication(-1)->expM().release();
    resMatrix = resMatrix->addition(1)->dividing(1, true).release();
    return unique_ptr<IMatrix<double>>(resMatrix);
}

template<typename T>
unique_ptr<IMatrix<double>>
ActivationFunctions<T>::dsigmoid(IMatrix<T> *matrix)
{
    IMatrix<double> *resMatrix
        = sigmoid(matrix)->subtraction(1, true).release();
    resMatrix = sigmoid(matrix)->simplifiedMult(resMatrix).release();
    return unique_ptr<IMatrix<double>>(resMatrix);
}

template<typename T>
unique_ptr<IMatrix<double>>
ActivationFunctions<T>::tanh(IMatrix<T> *matrix)
{
    return matrix->tanhM();
}

template<typename T>
unique_ptr<IMatrix<double>>
ActivationFunctions<T>::dtanh(IMatrix<T> *matrix)
{
    IMatrix<double> *resMatrix
        = ActivationFunctions<double>::tanh(matrix)->simplifiedMult(
            ActivationFunctions<double>::tanh(matrix).release()
            ).release();
    resMatrix = resMatrix->subtraction(1, true).release();
    return unique_ptr<IMatrix<double>>(resMatrix);
}

template<typename T>
unique_ptr<IMatrix<double>>
ActivationFunctions<T>::softmax(const IMatrix<T> *matrix)
{
    if (matrix->type() == Dimensions::THREE) {
        vector<Matrix2d<double>> resultData3d;
        // при проходе по 3д матрице, вызываем этот же метод но для 2д подматриц
        for (const Matrix2d<double> &rowM : ((Matrix3d<double>*)matrix)->dataToVector()) {
            Matrix2d<double> stepMatrix(softmax(&rowM));
            resultData3d.push_back(stepMatrix);
        }
        return unique_ptr<Matrix3d<T>>(new Matrix3d(resultData3d));
    } else if (matrix->type() == Dimensions::TWO) {
        vector<vector<T>> resultData2d;
        // при проходе по 2д матрице, просто проходимся по каждой строчке
        for (const vector<double> &row : ((Matrix2d<double>*)matrix)->dataToVector()) {
            resultData2d.push_back(softmaxRow(row));
        }
        return unique_ptr<Matrix2d<double>>(new Matrix2d(resultData2d));
    } else {
        throw ActivationFunctionsException(
            QString("\nSoftmax exception \n[%1]\n")
                .arg("There is no implementation for the current matrix yet")
            );
    }
}
