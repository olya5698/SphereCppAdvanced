set(LIB_CODE
        "src/Server.cpp"
        "src/Connection.cpp"
        "src/Descriptor.cpp"
)

add_library(${LIB_NAME} STATIC ${LIB_CODE})
target_include_directories(${LIB_NAME} PUBLIC include)
