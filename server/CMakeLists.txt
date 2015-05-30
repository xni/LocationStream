cmake_minimum_required(VERSION 3.2)
project(LocationStreamServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost 1.58.0 REQUIRED COMPONENTS system)

include_directories(Boost_INCLUDE_DIRS)

set(SOURCE_FILES main.cpp)
add_executable(LocationStreamServer ${SOURCE_FILES})

target_link_libraries(LocationStreamServer ${Boost_LIBRARIES})
