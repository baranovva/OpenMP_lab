cmake_minimum_required(VERSION 3.26)
project(OpenMP_labs)

set(CMAKE_CXX_FLAGS "-fopenmp -O0")
set(CMAKE_CXX_STANDARD 23)

add_executable(OpenMP_labs "main.cpp")
