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

#endif // OPERATIONS_H
