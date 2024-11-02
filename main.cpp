#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <sstream>

#include "matrix.hpp"

// #define DEBUG

int main() {

#if defined(UNIT_TESTING) || defined(FULL_TESTING)

    testing::InitGoogleTest();
    auto r = RUN_ALL_TESTS();

#else

    SquareMatrix<MType> matrix;

#ifdef DEBUG

    std::cout << "Original Matrix:" << std::endl;
    matrix.dump();

#endif

    double det = matrix.getDet();

#ifdef DEBUG

    std::cout << "\nUpper Triangular Matrix:" << std::endl;
    matrix.dump();
    std::cout << "\ndet - " << det << std::endl;

#else    

    std::cout << det << std::endl;

#endif

#endif
}

#ifdef FULL_TESTING

#define GTEST(number, type, fname)                                          \
TEST(count_det, number) {                                                   \
    double answer;                                                          \
    std::stringstream fTest(fname);                                         \
                                                                            \
    SquareMatrix<type> matrix(fTest);                                       \
    auto det = matrix.getDet();                                             \
                                                                            \
    fTest >> answer;                                                        \
                                                                            \
    EXPECT_NEAR(det, answer, 0.1);                                          \
}

GTEST(test1, int, "3 5 6 2 20 27 11 80 105 42  15")
GTEST(test2, float, "4 2 2 15 15 10 12 80 95 12 14 100 135 62 72 515 695  100")
GTEST(test3, short, "5 2 0 9 4 0 0 2 15 4 15 8 2 54 21 18 32 14 258 96 114 132 58 1065 396 474  36")
GTEST(test4, double, "6 2 10 0 2 4 4 10 55 0 14 32 28 50 270 4 74 160 148 230 1245 16 340 740 676 472 2555 32 694 1516 1392 2106 11400 144 3104 6768 6200  1280")
GTEST(test5, double, "7 3 1 3 10 20 16 5 0 1 0 2 25 16 10 0 1 1 6 35 36 35 0 9 4 36 290 236 195 0 23 8 82 710 572 455 3 126 48 462 3895 3152 2520 15 205 88 776 6295 5108 4070  600")

#endif

#ifdef UNIT_TESTING   

TEST(MyVector, MyVectorFuncTest1) {

    MyVector<int> vector;
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);

    // size_t sz = vector.get_size();

    EXPECT_EQ(1, vector[0]);
    EXPECT_EQ(2, vector[1]);
    EXPECT_EQ(3, vector[2]);
    // EXPECT_EQ(3, sz);
}

TEST(MyVector, MyVectorFuncTest2) {

    MyVector<int> vector;
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);

    size_t sz = vector.get_size();
    EXPECT_EQ(3, sz);
}

TEST(MyVector, MyVectorFuncTest3) {

    MyVector<int> vector;
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);

    vector.resize(2);

    EXPECT_EQ(1, vector[0]);
    EXPECT_EQ(2, vector[1]);
}

#endif