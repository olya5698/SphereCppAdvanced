cmake_minimum_required(VERSION 3.15)

set(LIB_CODE
        "src/BaseLogger.cpp"
        "src/StdoutLogger.cpp"
        "src/StderrLogger.cpp"
        "src/FileLogger.cpp"
        "src/Level.cpp"
        "src/Logger.cpp"
        "src/LoggerFunctions.cpp"
        "src/Exception.cpp"
)

add_library(${LIB_NAME} STATIC ${LIB_CODE})
target_include_directories(${LIB_NAME} PUBLIC include)
