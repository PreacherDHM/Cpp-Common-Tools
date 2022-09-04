cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Common VERSION 0.1 DESCRIPTION "The Common lib has all of the data that is shared between the server and the cliant")

add_library(${PROJECT_NAME} SHARED src/CommonLib.cpp includes/CommonLib.h)

target_include_directories(${PROJECT_NAME} PRIVATE includes)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER includes/CommonLib.h)

enable_testing()
add_subdirectory(tests)
