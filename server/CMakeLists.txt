cmake_minimum_required(VERSION 3.10.2)
project(TownOfSalemServer)

set(CMAKE_CXX_STANDARD 17)

set(TARGET_NAME TownOfSalemServer)
add_executable(${TARGET_NAME} main.cpp)
target_link_libraries(${TARGET_NAME} Ws2_32)