cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(_template_lib)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE LIB_SOURCES *.cpp *.h)

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

