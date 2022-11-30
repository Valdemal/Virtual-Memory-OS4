cmake_minimum_required(VERSION 3.23)
project(OS4)

set(CMAKE_CXX_STANDARD 20)

add_executable(OS4 main.cpp HeapManager.cpp HeapManager.h)
