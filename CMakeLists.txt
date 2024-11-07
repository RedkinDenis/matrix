# cmake -DCMAKE_BUILD_TYPE=Release -S . -B build

cmake_minimum_required(VERSION 3.10)
project(matrix)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

find_package(GTest REQUIRED)

add_library(mtr INTERFACE)

target_include_directories(mtr INTERFACE ${INCLUDE_DIR})


add_library(TEST INTERFACE)

target_include_directories(TEST INTERFACE ${GTEST_INCLUDE_DIRS})
target_include_directories(TEST INTERFACE ${INCLUDE_DIR})


add_library(UNIT_TEST INTERFACE)

target_include_directories(UNIT_TEST INTERFACE ${GTEST_INCLUDE_DIRS})
target_include_directories(UNIT_TEST INTERFACE ${INCLUDE_DIR})


add_executable(matrix.x main.cpp)                                                         
target_link_libraries(matrix.x mtr)


add_executable(matrix.test main.cpp)                                                         
target_link_libraries(matrix.test TEST)
target_link_libraries(matrix.test ${GTEST_LIBRARIES})
target_compile_definitions(matrix.test PRIVATE FULL_TESTING)


add_executable(matrix.unit main.cpp)                                                         
target_link_libraries(matrix.unit UNIT_TEST)
target_link_libraries(matrix.unit ${GTEST_LIBRARIES})
target_compile_definitions(matrix.unit PRIVATE UNIT_TESTING)
