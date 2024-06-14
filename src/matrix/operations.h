#ifndef OPERATIONS_H
#define OPERATIONS_H

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

#endif // OPERATIONS_H
