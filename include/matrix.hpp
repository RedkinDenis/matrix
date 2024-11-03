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

template<typename Type>
class SquareMatrix {
    using T = typename std::conditional<std::is_integral<Type>::value, double, Type>::type;
public:

    SquareMatrix (MyVector<MyVector<T>> &setData) {
        data = setData;
    }

    SquareMatrix (std::stringstream &inp) {

        MyVector<MyVector<T>> d = getMatrixData(inp);
        data = d;
    }

    SquareMatrix (std::ifstream &inp) {

        MyVector<MyVector<T>> d = getMatrixData(inp);
        data = d;
    }

    SquareMatrix () {

        MyVector<MyVector<T>> d = getMatrixData();
        data = d;
    }

    T getDet () {

        int sign = 1;
        if (!ToTriangular(sign))
            return 0;

        return sign * countDet();
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

private:

    MyVector<MyVector<T>> data;
    size_t mSize = 0;
    
    bool ToTriangular(int &sign) {

        for (int i = 0; i < mSize; ++i) {

            int maxRow = getMaxLine(i);

            // Changing the current line from the maximum
            if (maxRow != i) {

                std::swap(data[i], data[maxRow]);
                sign *= -1;
            }

            if (std::abs(data[i][i]) < 1e-9) {
                return false;
            }

            subtractLine(i);
        }
        return true;
    }  

    int getMaxLine (int i) {

        T maxElement = std::abs(data[i][i]);
        int maxRow = i;

        for (int k = i + 1; k < mSize; ++k) {

            if (std::abs(data[k][i]) > maxElement) {

                maxElement = std::abs(data[k][i]);
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

    template <typename StreamType>
    MyVector<MyVector<T>> getMatrixData(StreamType& inp) {
        T tmp = 0;
        size_t sz = 0;
        inp >> sz;
        mSize = sz;

        MyVector<MyVector<T>> data;

        for (size_t i = 0; i < sz; i++) {
            MyVector<T> vec;
            for (size_t j = 0; j < sz; j++) {
                inp >> tmp;
                vec.push_back(tmp);
            }
            data.push_back(vec);
        }

        return data;
    }

    MyVector<MyVector<T>> getMatrixData() {
        return getMatrixData(std::cin);
    }

    T countDet () {

        T det = data[0][0];

        for (int i = 1; i < mSize; i++) {

            det *= data[i][i];
        }
        return det;
    }
};
