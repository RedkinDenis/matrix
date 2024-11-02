#include "matrix.hpp"

MyVector<MyVector<double>> getMatrixData() {
    double tmp = 0;
    size_t sz = 0;
    std::cin >> sz;

    MyVector<MyVector<double>> data;

    for (size_t i = 0; i < sz; i++) {
        MyVector<double> vec;
        for (size_t j = 0; j < sz; j++) {
            std::cin >> tmp;
            vec.push_back(tmp);
        }
        data.push_back(vec); 
    }

    return data;
}

MyVector<MyVector<double>> getMatrixData (std::ifstream &inp) {
    double tmp = 0;
    size_t sz = 0;
    inp >> sz;

    MyVector<MyVector<double>> data;

    for (size_t i = 0; i < sz; i++) {
        MyVector<double> vec;
        for (size_t j = 0; j < sz; j++) {
            inp >> tmp;
            vec.push_back(tmp);
        }
        data.push_back(vec); 
    }

    return data;
}

MyVector<MyVector<double>> getMatrixData (std::stringstream &inp) {
    double tmp = 0;
    size_t sz = 0;
    inp >> sz;

    MyVector<MyVector<double>> data;

    for (size_t i = 0; i < sz; i++) {
        MyVector<double> vec;
        for (size_t j = 0; j < sz; j++) {
            inp >> tmp;
            vec.push_back(tmp);
        }
        data.push_back(vec); 
    }

    return data;
}