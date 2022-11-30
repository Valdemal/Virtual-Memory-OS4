cmake_minimum_required(VERSION 3.23)
project(OS4)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
        HeapManager.cpp HeapManager.h)

add_executable(CASE1 case1.cpp ${SOURCES})
add_executable(CASE2 case2.cpp ${SOURCES})
add_executable(CASE3 case3.cpp ${SOURCES})
add_executable(CASE4 case4.cpp ${SOURCES})