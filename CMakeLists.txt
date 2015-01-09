cmake_minimum_required(VERSION 2.8.4)
project(PORR)

# Boost
set(Boost_INCLUDE_DIR /usr/local/Cellar/boost/1.57.0/include)
set(Boost_LIBRARY_DIR /usr/local/Cellar/boost/1.57.0/lib)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

# Log4cxx
find_package(PkgConfig)
pkg_check_modules(LOG4CXX REQUIRED liblog4cxx)
include_directories(${LOG4CXX_INCLUDE_DIRS})
link_directories(${LOG4CXX_LIBRARY_DIRS})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(CMAKE_CXX_COMPILER /usr/local/Cellar/gcc49/4.9.2_1/bin/g++-4.9)

set(SOURCE_FILES
    main.cpp
    Population.h Population.cpp
    Individual.h Individual.cpp)

add_executable(PORR ${SOURCE_FILES})
target_link_libraries( PORR ${Boost_LIBRARIES} )

# Unit tests
enable_testing()
add_executable(PORR_test
    Population.h Population.cpp
    Individual.h Individual.cpp
    test/IndividualTest.cpp)
add_test(PORR_test ${CMAKE_CURRENT_BINARY_DIR}/PORR_test)