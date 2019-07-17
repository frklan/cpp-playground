cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(sscanf)

#set (CMAKE_CXX_STANDARD 17)
#set (CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SOURCE_FILES *.c)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
