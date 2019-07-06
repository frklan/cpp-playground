cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(clioptions)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SOURCE_FILES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Boost
find_package(Boost 1.60 REQUIRED COMPONENTS
  program_options)
target_link_libraries(${PROJECT_NAME} Boost::program_options)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
