cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(nano)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SOURCE_FILES *.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

#add_subdirectory(${PROJECT_NAME}_lib)
#target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)

target_link_libraries(${PROJECT_NAME} PUBLIC version)

# nanogui
include(cmake/nanogui.cmake)
target_link_libraries(${PROJECT_NAME} PRIVATE ${NANOGUI_EXTRA_LIBS} nanogui)
