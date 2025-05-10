cmake_minimum_required(VERSION 3.10.0)
project(SimpleGraphicsEngine VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

include_directories(${CMAKE_SOURCE_DIR}/Engine)

set_target_properties(SimpleGraphicsEngine PROPERTIES LINK_FLAGS "-static -static-libgcc -static-libstdc++ -mwindows")
