cmake_minimum_required(VERSION 3.26)
project(OpenMP_labs)

set(CMAKE_CXX_FLAGS "-fopenmp")
set(CMAKE_CXX_STANDARD 23)

add_executable(OpenMP_labs main.cpp
        "Lab 1/omp_section_3d.c")
