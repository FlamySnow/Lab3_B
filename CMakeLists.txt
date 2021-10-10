cmake_minimum_required(VERSION 3.20)
project(Lab3_B)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab3_B main.cpp)

find_library(LIB_PATH PCB
        PATHS
        ./lib/cmake-build-debug/)

target_include_directories(Lab3_B PRIVATE ./lib)

TARGET_LINK_LIBRARIES( Lab3_B ${LIB_PATH} )
