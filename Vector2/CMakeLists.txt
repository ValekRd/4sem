cmake_minimum_required(VERSION 3.6)
project(Vector2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp vector2.h vector2.cpp)
add_executable(main ${SOURCE_FILES})