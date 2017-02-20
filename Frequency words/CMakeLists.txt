cmake_minimum_required(VERSION 3.6)
project(frequency_words)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Debug/file.txt)
add_executable(frequency_words ${SOURCE_FILES})