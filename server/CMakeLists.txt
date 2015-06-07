cmake_minimum_required(VERSION 3.2)
project(LocationStreamServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost 1.54.0 REQUIRED COMPONENTS system)

include_directories(Boost_INCLUDE_DIRS)

set(SOURCE_FILES main.cpp)
add_executable(LocationStreamServer ${SOURCE_FILES})

target_link_libraries(LocationStreamServer ${Boost_LIBRARIES})


set(CHAT_MANAGER_FILES chat_manager.cpp)
find_package(Redis REQUIRED)
find_package(LibEV REQUIRED)
include_directories(${REDIS_INCLUDE_DIR})
include_directories(${LIBEV_INCLUDE_DIR})
add_executable(ChatManager ${CHAT_MANAGER_FILES} ChatRoom.cpp ChatRoom.h)
target_link_libraries(ChatManager ${REDIS_LIBRARY} ${LIBEV_LIBRARIES})