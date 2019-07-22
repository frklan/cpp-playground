cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(ncursescpp_lib)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_CLANG_TIDY
  clang-tidy;
  -header-filter="*.h";
  -checks=*,-*-vararg;
  )

file(GLOB_RECURSE LIB_SOURCES *.cpp *.h)
add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses) 
target_link_libraries(${PROJECT_NAME} PUBLIC ${CURSES_LIBRARIES})

find_package(ncursescpp REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC ncursescpp::ncursescpp)
