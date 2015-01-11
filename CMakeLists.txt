cmake_minimum_required(VERSION 2.8.4)
project(PORR)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wconversion -Wsign-conversion")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

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



# Unit tests
#enable_testing()
#add_executable(PORR_test
#    src/Population.h src/Population.cpp
#    src/Individual.h src/Individual.cpp
#    test/IndividualTest.cpp)
#add_test(PORR_test ${CMAKE_CURRENT_BINARY_DIR}/PORR_test)



# Boost
#set(Boost_INCLUDE_DIR /usr/local/Cellar/boost/1.57.0/include)
#set(Boost_LIBRARY_DIR /usr/local/Cellar/boost/1.57.0/lib)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS log log_setup thread date_time filesystem system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
#link_libraries(${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
# link_directories(${Boost_LIBRARY_DIR})
set(LIBS ${LIBS} ${Boost_LIBRARIES})
#add_definitions(WITboost_log)

message("include dirs= " ${Boost_INCLUDE_DIR} )
message("include libs= " ${Boost_LIBRARY_DIR} )


find_package(log4cxx REQUIRED)
include_directories(${LOG4CXX_INCLUDE_DIR})
set(LIBS ${LIBS} ${LOG4CXX_LIBRARIES})
ADD_DEFINITIONS(-DWITH_LOG4CXX)

#message("pobrane  = " ${LIBS} )
#message("include dirs= " ${LOG4CXX_INCLUDE_DIR} )
#message("include libs= " ${LOG4CXX_LIBRARIES} )

add_executable(PORR ${SOURCE_FILES})

target_link_libraries(PORR ${LIBS})
