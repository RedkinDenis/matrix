#include "matrix.hpp"

MyVector<MyVector<MType>> getMatrixData() {
    MType tmp = 0;
    size_t sz = 0;
    std::cin >> sz;

    MyVector<MyVector<MType>> data;

    for (size_t i = 0; i < sz; i++) {
        MyVector<MType> vec;
        for (size_t j = 0; j < sz; j++) {
            std::cin >> tmp;
            vec.push_back(tmp);
        }
        data.push_back(vec); 
    }

    return data;
}

MyVector<MyVector<MType>> getMatrixData (std::ifstream &inp) {
    MType tmp = 0;
    size_t sz = 0;
    inp >> sz;

    MyVector<MyVector<MType>> data;

    for (size_t i = 0; i < sz; i++) {
        MyVector<MType> vec;
        for (size_t j = 0; j < sz; j++) {
            inp >> tmp;
            vec.push_back(tmp);
        }
        data.push_back(vec); 
    }

    return data;
}

MyVector<MyVector<MType>> getMatrixData (std::stringstream &inp) {
    MType tmp = 0;
    size_t sz = 0;
    inp >> sz;

    MyVector<MyVector<MType>> data;

    for (size_t i = 0; i < sz; i++) {
        MyVector<MType> vec;
        for (size_t j = 0; j < sz; j++) {
            inp >> tmp;
            vec.push_back(tmp);
        }
        data.push_back(vec); 
    }

    return data;
}