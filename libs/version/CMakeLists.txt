cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(version)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_EXTENSIONS OFF)

add_custom_command(
  OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/makeversion.sh -o ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
)

file(GLOB_RECURSE LIB_SOURCES *.cpp *.h)

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/version.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})