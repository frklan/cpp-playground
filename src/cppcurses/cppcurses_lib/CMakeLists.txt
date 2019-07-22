cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(cppcurses_lib)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE LIB_SOURCES *.cpp *.h)
add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses) 
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})

#§target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)
target_link_libraries(${PROJECT_NAME} cppurses  pthread)
