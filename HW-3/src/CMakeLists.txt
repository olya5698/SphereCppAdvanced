add_executable(server server.cpp)
target_link_libraries(server ${LIB_NAME})

add_executable(client client.cpp)
target_link_libraries(client ${LIB_NAME})

add_executable(descriptor descriptor.cpp)
target_link_libraries(descriptor ${LIB_NAME})
