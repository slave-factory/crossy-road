cmake_minimum_required(VERSION 3.10)

project(
    CppProject
    VERSION 0.1
    DESCRIPTION "crossy-road-clone"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(main ${SOURCES})

target_link_libraries(main sfml-graphics sfml-window sfml-system)
include_directories(${PROJECT_SOURCE_DIR}/include)