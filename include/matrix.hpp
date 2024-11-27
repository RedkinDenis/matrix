#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <sstream>
#include <gtest/gtest.h>
#include <type_traits>

#include "myVector.hpp"

using MType = double;

// template <typename Type>
// using fT = typename std::conditional<std::is_integral<Type>::value, double, Type>::type;

template <typename TType>
MyVector<MyVector<TType>> getMatrixData(std::istream &inp = std::cin) {
    TType tmp = 0;
    int sz = 0;
    inp >> sz;

    MyVector<MyVector<TType>> data;

    if (sz <= 0) {
        throw std::runtime_error("matrix size must be >= 1");
    }

    for (size_t i = 0; i < sz; i++) {
        MyVector<TType> vec;
        for (size_t j = 0; j < sz; j++) {
            inp >> tmp;
            vec.push_back(tmp);
        }
        data.push_back(vec);
    }

    return data;
}


template<typename T>
class SquareMatrix {
    // using T = typename std::conditional<std::is_integral<Type>::value, double, Type>::type;
public:

    SquareMatrix (MyVector<MyVector<T>> &setData) {
        data = setData;
        mSize = data.get_size();
    }

    template <typename U>
    SquareMatrix (const SquareMatrix<U> &matrix) {

        MyVector<MyVector<double>> newData;
        for (int i = 0; i < matrix.data.get_size(); i++) {
            MyVector<double> vec;

            for (int j = 0; j < matrix.data[i].get_size(); j++)
                vec.push_back((double)matrix.data[i][j]);

            // std::transform(matrix.data[i].begin(), matrix.data[i].end(), std::back_inserter(vec), [](T x) { return (double)x; });
            newData.push_back(vec);
        }

        data = newData;
        mSize = data.get_size();
    }

    double getDet () {

        if (!std::is_integral<T>::value) {
            int sign = 1;
            if (!ToTriangular(sign))
                return 0;

            return sign * countDet();
        }
        SquareMatrix<double> dMatr(*this);
        return dMatr.getDet();
    }
    
    void dump() const {

        size_t sz = data.get_size();
        for (int i = 0; i < sz; i++) {

            for (int j = 0; j < sz; j++) {

                std::cout << std::setw(10) << std::fixed << std::setprecision(2) << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }      


    MyVector<MyVector<T>> data;
private:
    size_t mSize = 0;
    
    bool ToTriangular(int &sign) {

        for (int i = 0; i < mSize; ++i) {

            int maxRow = getMaxLine(i);

            // Changing the current line from the maximum
            if (maxRow != i) {

                std::swap(data[i], data[maxRow]);
                sign *= -1;
            }

            if (std::fabs(data[i][i]) < 1e-9) {
                return false;
            }

            subtractLine(i);
        }
        return true;
    }  

    int getMaxLine (int i) const {

        T maxElement = std::fabs(data[i][i]);
        int maxRow = i;

        for (int k = i + 1; k < mSize; ++k) {

            if (std::fabs(data[k][i]) > maxElement) {

                maxElement = std::fabs(data[k][i]);
                maxRow = k;
            }
        }
        return maxRow;
    } 

    void subtractLine (int i) {

        for (int k = i + 1; k < mSize; ++k) {

            double factor = data[k][i] / data[i][i];
            for (int j = i; j < mSize; ++j) {

                data[k][j] -= factor * data[i][j];
            }
        }
    }

    T countDet () const {

        T det = data[0][0];

        for (int i = 1; i < mSize; i++) {

            det *= data[i][i];
        }
        return det;
    }
};
