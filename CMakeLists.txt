cmake_minimum_required(VERSION 2.8)

project(Defense)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O0 -Werror -g")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O0 -Werror -g -rdynamic")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -Werror -g")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -Werror")

# Include libraries
find_package(GLFW3     REQUIRED)
find_package(GLEW      REQUIRED)
find_package(FreeType2 REQUIRED)
find_package(OpenGL    REQUIRED)

# Include freetype directories
# TODO: why?
include_directories(${FREETYPE_INCLUDE_DIR_freetype2})
include_directories(${FREETYPE_INCLUDE_DIR_ft2build})

# Include all... *ahem*
# all code directories
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

add_executable(
        ${PROJECT_NAME}
        src/defense.cpp
        ${SOURCES}
        ${HEADERS} src/common/CircularBuffer.cpp src/common/CircularBuffer.hpp src/graphics/GraphicsBackend.cpp src/graphics/GraphicsBackend.hpp)

# TODO: why do I need -lfreetype? What's ${FREETYPE2_LIBRARY} for?
target_link_libraries(
        ${PROJECT_NAME}
        ${GLFW3_LIBRARIES}
        ${GLEW_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${FREETYPE2_LIBRARY}
        glfw
        GLEW
        -lfreetype)
