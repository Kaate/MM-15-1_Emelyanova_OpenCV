cmake_minimum_required(VERSION 3.0)

project(laba2)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(laba2 laba2.cpp)
target_link_libraries(laba2 ${OpenCV_LIBS})