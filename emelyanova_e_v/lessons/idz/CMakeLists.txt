cmake_minimum_required(VERSION 3.0)

project(idz)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(idz idz.cpp)
target_link_libraries(idz ${OpenCV_LIBS})