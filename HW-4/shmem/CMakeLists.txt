set(LIB_CODE
        "src/SemLock.cpp"
        "src/Semaphore.cpp"
)

add_library(${LIB_NAME} STATIC ${LIB_CODE})
target_include_directories(${LIB_NAME} PUBLIC include)
