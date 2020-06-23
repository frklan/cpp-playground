cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(qt-qui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Microsoft.GSL CONFIG)


IF(WIN32)
  SET(GUI_TYPE WIN32)
ENDIF(WIN32)
IF (APPLE)
  SET(GUI_TYPE MACOSX_BUNDLE)
ENDIF (APPLE)


file(GLOB SOURCE_FILES *.cpp)
add_executable(${PROJECT_NAME} ${GUI_TYPE} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Microsoft.GSL::GSL)

