cmake_minimum_required(VERSION 3.13)
set(PROJECT_NAME TownOfSalem)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
set(SFML_ROOT D:/sfml)
set(SFML_STATIC_LIBARARIES TRUE)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
add_executable(${PROJECT_NAME} main.cpp Caret.cpp Caret.h Chat.h Chat.cpp Client.h Client.cpp Graveyard.h Graveyard.cpp Interface.h Interface.cpp Minibox.h Minibox.cpp Role.h Role.cpp Rolecard.h Rolecard.cpp Rolelist.h Rolelist.cpp Townies.h Townies.cpp TownOfSalem.h TownOfSalem.cpp Will.h Will.cpp)
link_directories(D:/sfml)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME} Ws2_32)

find_package(SFML 2 REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()