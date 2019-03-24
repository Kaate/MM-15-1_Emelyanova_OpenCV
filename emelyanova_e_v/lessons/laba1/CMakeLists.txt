cmake_minimum_required(VERSION 3.0)

project(laba1)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(laba1 laba1.cpp)
target_link_libraries(laba1 ${OpenCV_LIBS})