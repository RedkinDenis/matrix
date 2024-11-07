# cmake -DCMAKE_BUILD_TYPE=Release -S . -B build

cmake_minimum_required(VERSION 3.10)
project(matrix)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

find_package(GTest REQUIRED)

SET(SRCS
src/matrix.cpp
)

add_library(mtr STATIC ${SRCS})

target_include_directories(mtr PUBLIC ${INCLUDE_DIR})


add_library(TEST STATIC ${SRCS})

target_include_directories(TEST PUBLIC ${GTEST_INCLUDE_DIRS})
target_include_directories(TEST PUBLIC ${INCLUDE_DIR})


add_library(UNIT_TEST STATIC ${SRCS})

target_include_directories(UNIT_TEST PUBLIC ${GTEST_INCLUDE_DIRS})
target_include_directories(UNIT_TEST PUBLIC ${INCLUDE_DIR})


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
