cmake_minimum_required(VERSION 2.8)

project(Defense)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

# SDL2, SDL2/SDL2_Image, SDL2/SDL2_ttf
find_package(SDL2 REQUIRED)
find_package(SDL2_Image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2IMAGE_INCLUDE_DIR}
        ${SDL2TTF_INCLUDE_DIR})

# Defense
include_directories(src/)
file(GLOB SOURCES src/*.cpp src/*.c src/*/*.cpp src/*/*.c src/*/*/*.cpp src/*/*/*.c include/*/*.cpp include/*/*.c)
file(GLOB HEADERS src/*.hpp src/*.h src/*/*.hpp src/*/*.h src/*/*/*.hpp src/*/*/*.h include/*/*.hpp include/*/*.h)


add_executable(${PROJECT_NAME} src/defense.cpp ${SOURCES} ${HEADERS} src/TdECS/TdECSEntity.cpp src/TdECS/TdECSEntity.hpp src/TdECS/TdECSSystems/TdECSGraphicsSystem.cpp src/TdECS/TdECSSystems/TdECSGraphicsSystem.hpp src/TdECS/TdECSSystems/TdECSPhysicsSystem.cpp src/TdECS/TdECSSystems/TdECSPhysicsSystem.hpp src/TdECS/TdECSSystems/TdECSPlanningSystem.cpp src/TdECS/TdECSSystems/TdECSPlanningSystem.hpp src/TdECS/TdECSSystems/TdECSSystem.cpp src/TdECS/TdECSSystems/TdECSSystem.hpp src/TdECS/TdECSComponents/TdECSGraphicsComponent.cpp src/TdECS/TdECSComponents/TdECSGraphicsComponent.hpp src/TdECS/TdECSComponents/TdECSHealthComponent.cpp src/TdECS/TdECSComponents/TdECSHealthComponent.hpp src/TdECS/TdECSComponents/TdECSShooterComponent.cpp src/TdECS/TdECSComponents/TdECSShooterComponent.hpp src/TdECS/TdECSComponents/TdECSFighterComponent.cpp src/TdECS/TdECSComponents/TdECSFighterComponent.hpp src/TdECS/TdECSComponents/TdECSPositionComponent.cpp src/TdECS/TdECSComponents/TdECSPositionComponent.hpp src/TdECS/TdECSComponents/TdECSComponent.cpp src/TdECS/TdECSComponents/TdECSComponent.hpp src/TdECS/TdECSComponents/TdECSPhysicsComponent.cpp src/TdECS/TdECSComponents/TdECSPhysicsComponent.hpp src/TdECS/TdECSComponents/TdECSShapeComponent.cpp src/TdECS/TdECSComponents/TdECSShapeComponent.hpp src/TdECS/TdECSComponents/TdECSTilePositionComponent.cpp src/TdECS/TdECSComponents/TdECSTilePositionComponent.hpp)
target_link_libraries(${PROJECT_NAME}
        ${SDL2_LIBRARY}
        ${SDL2IMAGE_LIBRARY}
        ${SDL2TTF_LIBRARY})

