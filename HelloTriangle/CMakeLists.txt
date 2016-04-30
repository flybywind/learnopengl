cmake_minimum_required(VERSION 3.2)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.10)
project(HelloTriangle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
set(LIB_PATH "/usr/local/lib")
include_directories(/usr/local/include)
link_directories(${LIB_PATH})

file(GLOB MAIN src/main.cpp)
find_package(OPENGL REQUIRED)
message(STATUS "libraries path: ${LIB_PATH}")
find_library(GLEW_LIB
    NAMES GLEW
    PATHS ${LIB_PATH})
find_library(GLFW_LIB
    NAMES glfw
    PATHS ${LIB_PATH})

message(STATUS "libraries: ${OPENGL_LIBRARIES} ${GLEW_LIB} ${GLFW_LIB}")
message(STATUS "project name: ${PROJECT_NAME}")

add_executable(${PROJECT_NAME} ${MAIN})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLEW_LIB} ${GLFW_LIB})
