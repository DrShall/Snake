cmake_minimum_required(VERSION 3.5)

project(Snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Snake SnakeUnit.h main.cpp SnakeUnit.cpp)
