cmake_minimum_required(VERSION 3.15)

set(LIB_CODE
        "src/process.cpp"
)

add_library(${LIB_NAME} STATIC ${LIB_CODE})
target_include_directories(${LIB_NAME} PUBLIC include)
