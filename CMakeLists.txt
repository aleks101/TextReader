cmake_minimum_required(VERSION 3.11)

project(2DGame)

set(GLEW_ROOT ${CMAKE_SOURCE_DIR}/Dependencies/GLEW/glew-2.2.0) #change the path if necessary
message(STATUS "GLEW_ROOT: ${GLEW_ROOT}")

add_subdirectory(Dependencies)
add_subdirectory(Source)
add_subdirectory(Include)