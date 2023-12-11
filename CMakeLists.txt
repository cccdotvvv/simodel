cmake_minimum_required(VERSION 3.26.0)
project(simodel)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(simodel main.cpp ${SOURCES})