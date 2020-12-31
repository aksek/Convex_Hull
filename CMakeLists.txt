cmake_minimum_required(VERSION 3.17)
project(ConvexHull)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ConvexHull src/main.cpp src/Point.hpp src/Point.cpp src/preprocessing.hpp src/preprocessing.cpp 
src/Triangle.hpp src/Triangle.cpp src/Vector.hpp src/Vector.cpp src/naive_solver.hpp src/naive_solver.cpp)
