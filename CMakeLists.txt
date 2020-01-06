cmake_minimum_required(VERSION 3.14)
project(serailIMU)

set(CMAKE_CXX_STANDARD 14)

add_executable(serailIMU main.cpp stdint.h Com.h Com.cpp)