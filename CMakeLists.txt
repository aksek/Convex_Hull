cmake_minimum_required(VERSION 3.17)
project(ConvexHull)

set(CMAKE_CXX_STANDARD 14)

add_executable(ConvexHull src/main.cpp src/Point.hpp src/Point.cpp src/preprocessing.hpp src/preprocessing.cpp)
