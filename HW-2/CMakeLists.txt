cmake_minimum_required(VERSION 3.15)
project(hw-2)

set(CMAKE_CXX_STANDARD 17)
set(LIB_NAME log)

add_subdirectory(log)
add_executable(hw-2 src/main.cpp)
target_link_libraries(hw-2 ${LIB_NAME}) 
