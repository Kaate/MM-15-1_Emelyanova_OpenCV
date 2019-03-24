cmake_minimum_required(VERSION 3.0)

project(kr1)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(kr1 kr1.cpp)
target_link_libraries(kr1 ${OpenCV_LIBS})