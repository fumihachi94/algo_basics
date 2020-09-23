cmake_minimum_required(VERSION 3.0.0)
project(bubble_sort VERSION 0.1.0)

add_executable(${PROJECT_NAME} main.cpp bubble_sort.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./build)

