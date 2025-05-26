cmake_minimum_required(VERSION 3.16.0)
project(SimpleGraphicsEngine VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(External/SDL)
add_subdirectory(External/glm)
add_subdirectory(External/bullet3)

set(SOURCES
    main.cpp
    Engine/Engine.cpp
    Engine/Scene/Scene.cpp
    Engine/Scene/Subsystems/EventProcessingSubsystem.cpp
    Engine/Scene/Subsystems/GraphicsSubsystem.cpp
    Engine/Scene/Subsystems/InputProcessingSubsystem.cpp
    Engine/Scene/Subsystems/KinematicsSubsystem.cpp
    Engine/Scene/Subsystems/PhysicsSubsystem.cpp
    Engine/Scene/Subsystems/RaycastSubsystem.cpp
    Engine/Windows/MainWindow.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

set(BOOST_LIBS ${CMAKE_SOURCE_DIR}/External/boost/libs)

target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/pch.h)

set(OPENGL_INCLUDE_DIRECTORY E:/apps/msys64/ucrt64/include/GL)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${OPENGL_INCLUDE_DIRECTORY}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Engine
    ${CMAKE_SOURCE_DIR}/External/glm
    ${CMAKE_SOURCE_DIR}/External/SDL/include
    ${CMAKE_SOURCE_DIR}/External/bullet3/src
    ${BOOST_LIBS}/assert/include
    ${BOOST_LIBS}/bind/include
    ${BOOST_LIBS}/config/include
    ${BOOST_LIBS}/container_hash/include
    ${BOOST_LIBS}/core/include
    ${BOOST_LIBS}/describe/include
    ${BOOST_LIBS}/integer/include
    ${BOOST_LIBS}/iterator/include
    ${BOOST_LIBS}/move/include
    ${BOOST_LIBS}/mp11/include
    ${BOOST_LIBS}/mpl/include
    ${BOOST_LIBS}/multi_index/include
    ${BOOST_LIBS}/preprocessor/include
    ${BOOST_LIBS}/static_assert/include
    ${BOOST_LIBS}/throw_exception/include
    ${BOOST_LIBS}/tuple/include
    ${BOOST_LIBS}/type_traits/include
    ${BOOST_LIBS}/utility/include
)

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3 OpenGL::GL glu32 BulletDynamics BulletCollision LinearMath)

# Это переносит SDL3.dll в папку к exe
set(SDL_DLL_PATH ${CMAKE_SOURCE_DIR}/build/lib/SDL3.dll)
set(OUTPUT_DLL_DIR ${CMAKE_SOURCE_DIR}/build)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${SDL_DLL_PATH}
    ${OUTPUT_DLL_DIR}
)
