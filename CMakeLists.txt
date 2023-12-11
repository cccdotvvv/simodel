cmake_minimum_required(VERSION 3.26.0)
project(simodel)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(simodel main.cpp ${SOURCES})