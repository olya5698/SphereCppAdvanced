cmake_minimum_required(VERSION 3.15)
project(hw-1)

set(CMAKE_CXX_STANDARD 17)
set(LIB_NAME lib)

add_subdirectory(lib)
add_executable(hw-1 src/main.cpp)
target_link_libraries(hw-1 ${LIB_NAME}) 
