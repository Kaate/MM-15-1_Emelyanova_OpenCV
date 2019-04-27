cmake_minimum_required(VERSION 3.0)

project(diplom)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(diplom diplom.cpp)
target_link_libraries(diplom ${OpenCV_LIBS})