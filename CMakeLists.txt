cmake_minimum_required(VERSION 2.8.4)
project(PORR)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp -Wno-conversion-null")

set(CMAKE_CXX_COMPILER /usr/local/Cellar/gcc49/4.9.2_1/bin/g++-4.9)
#set(CMAKE_CXX_COMPILER /usr/bin/c++)

set(HEADER_FILES
    src/Utils.h
    src/Population.h
    src/Individual.h)

set(SOURCE_FILES
    src/main.cpp
    src/Utils.cpp
    src/Population.cpp
    src/Individual.cpp)

add_executable(PORR ${SOURCE_FILES})
