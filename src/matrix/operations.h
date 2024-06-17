#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <vector>
#include <cmath>
using namespace std;

///
/// \brief The OperationType enum
/// определение вида операции для ее изменения
enum class OperationType {
    SUM, SUB, MUL, DIV
};

///
/// \brief The Operations class
/// класс с вынесенными основными
/// статическими простейшими операциями
template<typename T>
class Operations
{
public:
    static T sum(T a, T b);
    static T sub(T a, T b);
    static T mul(T a, T b);
    static T div(T a, T b);
    static T logM(T mainParam, T extraParam);
    static T expM(T mainParam, T extraParam);
    static T tanhM(T mainParam, T extraParam);
    static T clipM(T mainParam, T leftBorder);
    static T floorM(T mainParam, T numOfDecimal);
};

template<typename T>
T Operations<T>::sum(T a, T b)
{
    return a + b;
}

template<typename T>
T Operations<T>::sub(T a, T b)
{
    return a - b;
}

template<typename T>
T Operations<T>::mul(T a, T b)
{
    return a * b;
}

template<typename T>
T Operations<T>::div(T a, T b)
{
    return a / b;
}

template<typename T>
T Operations<T>::logM(T mainParam, T extraParam)
{
    return log(mainParam);
}

template<typename T>
T Operations<T>::expM(T mainParam, T extraParam)
{
    return exp(mainParam);
}

template<typename T>
T Operations<T>::tanhM(T mainParam, T extraParam)
{
    return tanh(mainParam);
}

template<typename T>
T Operations<T>::clipM(T mainParam, T leftBorder)
{
    T rightBorder = 1 - leftBorder;
    T newValue;
    if (mainParam <= leftBorder) {
        newValue = leftBorder;
    } else if (mainParam >= rightBorder) {
        newValue = rightBorder;
    } else {
        newValue = mainParam;
    }
    return newValue;
}

template<typename T>
T Operations<T>::floorM(T mainParam, T numOfDecimal)
{
    int multiplier = pow(10, numOfDecimal);
    return floor(mainParam * multiplier) / multiplier;
}

#endif // OPERATIONS_H
