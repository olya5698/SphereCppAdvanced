cmake_minimum_required(VERSION 3.15)
project(hw-1)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)
add_library(process lib/process.cpp)
add_executable(hw-1 src/main.cpp)
target_link_libraries(hw-1 process)
