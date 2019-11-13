cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(ctimer_lib)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_EXTENSIONS OFF)



file(GLOB_RECURSE LIB_SOURCES *.cpp *.h)
add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} version)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(NCURSESPP REQUIRED ncurses++w)
PKG_SEARCH_MODULE(NCURSES REQUIRED ncursesw)
PKG_SEARCH_MODULE(NCURSESPANEL REQUIRED panelw)

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${NCURSESPP_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${NCURSES_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${NCURSESPANEL_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} 
  ${NCURSESPP_LIBRARIES}
  ${NCURSES_LIBRARIES}
  ${NCURSESPANEL_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} redeo)

# Boost
find_package(Boost 1.70 REQUIRED COMPONENTS system)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
