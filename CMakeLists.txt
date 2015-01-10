cmake_minimum_required(VERSION 2.8.4)
project(PORR)

# Boost
set(Boost_INCLUDE_DIR /usr/local/Cellar/boost/1.57.0/include)
set(Boost_LIBRARY_DIR /usr/local/Cellar/boost/1.57.0/lib)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wconversion -Wsign-conversion")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(CMAKE_CXX_COMPILER /usr/local/Cellar/gcc49/4.9.2_1/bin/g++-4.9)
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
target_link_libraries( PORR ${Boost_LIBRARIES} )

# Unit tests
enable_testing()
add_executable(PORR_test
    src/Population.h src/Population.cpp
    src/Individual.h src/Individual.cpp
    test/IndividualTest.cpp)
add_test(PORR_test ${CMAKE_CURRENT_BINARY_DIR}/PORR_test)
