#include "matrix3d.h"

template<typename T>
Matrix3d<T>::Matrix3d()
{
}

template<typename T>
Matrix3d<T>::Matrix3d(vector<vector<vector<T>>> data)
    : data{data}
{
}

template<typename T>
Matrix3d<T>::Matrix3d(initializer_list<initializer_list<initializer_list<T>>> list)
{
    int depthIndex = 0;
    for (initializer_list<initializer_list<T>> matrix : list) {
        data.push_back(vector<vector<T>>());
        for (initializer_list<T> row : matrix) {
            data[depthIndex].push_back(row);
        }
        depthIndex++;
    }
}

template<typename T>
vector<vector<vector<T>>> Matrix3d<T>::transposition(const vector<vector<vector<T>>> matrix)
{

}
