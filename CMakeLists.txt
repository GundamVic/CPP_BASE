cmake_minimum_required(VERSION 3.10)
project(MyOpenCVProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)

add_executable(main leetcode.cpp)

target_link_libraries(main ${OpenCV_LIBS})

set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
