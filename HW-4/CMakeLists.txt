cmake_minimum_required(VERSION 3.15)
project(hw-4)

set(CMAKE_CXX_STANDARD 17)
set(LIB_NAME shmem)

add_subdirectory(shmem)
add_subdirectory(src)

target_link_libraries(${LIB_NAME} pthread)
