#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <sstream>
#include <gtest/gtest.h>

#include "myVector.hpp"

class SquareMatrix {

public:

    SquareMatrix (MyVector<MyVector<double>> &setData) {
        data = setData;
    }

    double getDet () {

        int sign = 1;
        if (!this->ToTriangular(sign))
            return 0;

        double det = data[0][0];

        size_t sz = data.get_size();
        for (int i = 1; i < sz; i++) {

            det *= data[i][i];
        }
        return det * sign;
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

    MyVector<MyVector<double>> data;
    
    bool ToTriangular(int &sign) {

        int n = data.get_size();

        for (int i = 0; i < n; ++i) {

            // Searching for the maximum element in the current column
            double maxElement = std::abs(data[i][i]);
            int maxRow = i;

            for (int k = i + 1; k < n; ++k) {

                if (std::abs(data[k][i]) > maxElement) {

                    maxElement = std::abs(data[k][i]);
                    maxRow = k;
                }
            }

            // Changing the current line from the maximum
            if (maxRow != i) {

                std::swap(data[i], data[maxRow]);
                sign *= -1;
            }

            if (std::abs(data[i][i]) < 1e-9) {
                return false;
            }

            // // // Bringing to the upper triangular view
            for (int k = i + 1; k < n; ++k) {

                double factor = data[k][i] / data[i][i];
                for (int j = i; j < n; ++j) {

                    data[k][j] -= factor * data[i][j];
                }
            }
        }
        return true;
    }  

};

MyVector<MyVector<double>> getMatrixData ();

MyVector<MyVector<double>> getMatrixData (std::ifstream &inp);

MyVector<MyVector<double>> getMatrixData (std::stringstream &inp);
