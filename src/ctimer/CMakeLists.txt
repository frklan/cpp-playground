cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(ctimer)

#add_subdirectory(${PROJECT_NAME}_lib)
add_subdirectory(curses_lib)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SOURCE_FILES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
#target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)
target_link_libraries(${PROJECT_NAME} PRIVATE curses_lib)

target_link_libraries(${PROJECT_NAME} PUBLIC version)
