cmake_minimum_required(VERSION 3.10)
project(FibonacciHeap)

set(CMAKE_CXX_STANDARD 11)
set(GLOB SOURCE_FILES *.cpp)
add_executable(FibonacciHeap main.cpp
               FiboHeap.cpp FiboHeap.h)