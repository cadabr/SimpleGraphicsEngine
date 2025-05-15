cmake_minimum_required(VERSION 3.16.0)
project(SimpleGraphicsEngine VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/SDL)
add_subdirectory(external/glm)

add_executable(${PROJECT_NAME}
    main.cpp
    Engine/Engine.cpp
    Engine/Subsystems/GraphicsSubsystem.cpp
)

set(BOOST_LIBS ${CMAKE_SOURCE_DIR}/external/boost/libs)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Engine
    ${CMAKE_SOURCE_DIR}/external/glm
    ${CMAKE_SOURCE_DIR}/external/SDL/include
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

target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/pch.h)

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3 OpenGL::GL)
