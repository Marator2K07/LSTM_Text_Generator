#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <vector>
#include <cmath>
#include <random>

using namespace std;

///
/// \brief The OperationType enum
/// определение вида операции для ее изменения
enum class OperationType {
    SUM, SUB, MUL, DIV, LOGM, EXPM, TANHM, CLIPM, FLOORM
};

///
/// \brief The Operations class
/// класс с вынесенными основными
/// статическими простыми и не очень операциями
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
    ///
    /// \brief floorM округление с точностью до
    /// numOfDecimal цифр после запятой
    /// \param mainParam число для округления
    /// \param numOfDecimal количество цифр после запятой
    /// \return округленное число
    static T floorM(T mainNum, T numOfDecimal);
    ///
    /// \brief gaussianDistribution нормальное(гауссово)
    /// распределение для получения случайного числа
    /// \param mean - центр распределения
    /// \param width - разброс(ширина) распределения
    /// \return случайное число
    static T gaussianDistribution(T mean, T width);
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
T Operations<T>::floorM(T mainNum, T numOfDecimal)
{
    int multiplier = pow(10, numOfDecimal);
    return floor(mainNum * multiplier) / multiplier;
}

template<typename T>
T Operations<T>::gaussianDistribution(T mean, T width)
{
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> distribution(mean, width);
    return distribution(gen);
}

#endif // OPERATIONS_H
