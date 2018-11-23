cmake_minimum_required(VERSION 2.8)

project(Defense)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -Werror -pg -g")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -Werror -g")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -Werror")

# SDL2, SDL2/SDL2_Image, SDL2/SDL2_ttf
find_package(SDL2 REQUIRED)
find_package(SDL2_Image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR})

# Defense
include_directories(src/)
file(GLOB SOURCES src/*.cpp src/*.c src/*/*.cpp src/*/*.c src/*/*/*.cpp src/*/*/*.c include/*/*.cpp include/*/*.c)
file(GLOB HEADERS src/*.hpp src/*.h src/*/*.hpp src/*/*.h src/*/*/*.hpp src/*/*/*.h include/*/*.hpp include/*/*.h)


add_executable(${PROJECT_NAME} src/defense.cpp ${SOURCES} ${HEADERS} src/TdECS/TdECSSystems/GraphicsSystem.cpp src/TdECS/TdECSSystems/GraphicsSystem.hpp src/TdECS/TdECSSystems/PhysicsSystem.cpp src/TdECS/TdECSSystems/PhysicsSystem.hpp src/TdECS/TdECSSystems/PlanningSystem.cpp src/TdECS/TdECSSystems/PlanningSystem.hpp src/TdECS/TdECSSystems/System.cpp src/TdECS/TdECSSystems/System.hpp src/TdECS/TdECSComponents/Graphics.cpp src/TdECS/TdECSComponents/Graphics.hpp src/TdECS/TdECSComponents/Health.cpp src/TdECS/TdECSComponents/Health.hpp src/TdECS/TdECSComponents/Position.cpp src/TdECS/TdECSComponents/Position.hpp src/TdECS/TdECSComponents/Component.cpp src/TdECS/TdECSComponents/Component.hpp src/TdECS/TdECSComponents/Physics.cpp src/TdECS/TdECSComponents/Physics.hpp src/TdECS/TdECSComponents/Shape.cpp src/TdECS/TdECSComponents/Shape.hpp src/TdECS/TdECSComponents/TilePosition.cpp src/TdECS/TdECSComponents/TilePosition.hpp src/TdECS/TdECSSystems/SystemUtils.hpp src/TdECS/TdECSSystems/HealthSystem.cpp src/TdECS/TdECSSystems/HealthSystem.hpp src/TdECS/TdECSSystems/SystemUtils.cpp src/TdECS/TdECSComponents/LaserShooter.cpp src/TdECS/TdECSComponents/LaserShooter.hpp src/TdECS/TdECSComponents/Attack.cpp src/TdECS/TdECSComponents/Attack.hpp src/TdECS/TdECSComponents/Pathing.cpp src/TdECS/TdECSComponents/Pathing.hpp src/TdECS/TdECSSystems/CollisionSystem.cpp src/TdECS/TdECSSystems/CollisionSystem.hpp src/TdECS/TdECSSystems/TdCollisionQuadTree/QuadTree.cpp src/TdECS/TdECSSystems/TdCollisionQuadTree/QuadTree.hpp src/TdECS/TdECSSystems/TdCollisionQuadTree/Node.cpp src/TdECS/TdECSSystems/TdCollisionQuadTree/Node.hpp src/TdECS/TdECSSystems/SystemPosUtils.hpp src/TdECS/TdECSSystems/Rect.cpp src/TdECS/TdECSSystems/Rect.hpp)
target_link_libraries(${PROJECT_NAME}
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        ${SDL2_TTF_LIBRARY})
