cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(qt-qui-ui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Microsoft.GSL CONFIG)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

IF(WIN32)
  SET(GUI_TYPE WIN32)
ENDIF(WIN32)
IF (APPLE)
  SET(GUI_TYPE MACOSX_BUNDLE)
ENDIF (APPLE)

file(GLOB SOURCE_FILES *.cpp)
file(GLOB HEADER_FILES *.h)
file(GLOB UI_FILES *.ui)

qt5_wrap_ui(ui_wrap ${UI_FILES})
qt5_wrap_cpp(moc_sources ${HEADER_FILES})

add_executable(${PROJECT_NAME} ${GUI_TYPE} ${SOURCE_FILES} ${ui_wrap} ${HEADER_FILES} ${moc_sources})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Microsoft.GSL::GSL)

