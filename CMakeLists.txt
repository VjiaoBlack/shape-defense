cmake_minimum_required(VERSION 2.8)

project(Defense)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O0 -Werror -pg -g")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -Werror -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -Werror")

# SDL2, SDL2/SDL2_Image, SDL2/SDL2_ttf
find_package(SDL2 REQUIRED)
find_package(SDL2_Image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR})

# Defense
include_directories(src/)
file(GLOB SOURCES
        src/*.cpp
        src/*.c
        src/*/*.cpp
        src/*/*.c
        src/*/*/*.cpp
        src/*/*/*.c
        src/*/*/*/*.cpp
        src/*/*/*/*.c)
file(GLOB HEADERS
        src/*.hpp
        src/*.h
        src/*/*.hpp
        src/*/*.h
        src/*/*/*.hpp
        src/*/*/*.h
        src/*/*/*/*.hpp
        src/*/*/*/*.h)


add_executable(${PROJECT_NAME} src/defense.cpp ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME}
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        ${SDL2_TTF_LIBRARY})
