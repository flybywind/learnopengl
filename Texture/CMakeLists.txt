cmake_minimum_required(VERSION 3.2)
# 我的系统不会自动设置target版本，Xcode7上就无法运行，提示系统版本低。所以在这里显示设置一下。
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.10)
project(Texture)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
set(LIB_PATH "/usr/local/lib")
include_directories(/usr/local/include)
link_directories(${LIB_PATH})

file(GLOB CPPSRC src/*.cpp)
file(GLOB HEADERSRC src/*.hpp)
# opengl可以直接通过find_package获得。
find_package(OPENGL REQUIRED)
# glfw和GLEW搜索lib_path获得。
find_library(GLEW_LIB
    NAMES GLEW
    PATHS ${LIB_PATH})
find_library(GLFW_LIB
    NAMES glfw
    PATHS ${LIB_PATH})
find_library(SOIL_LIB
    NAMES SOIL
    PATHS ${LIB_PATH})

message(STATUS "libraries: ${OPENGL_LIBRARIES} ${GLEW_LIB} ${GLFW_LIB} ${SOIL_LIB}")
message(STATUS "project name: ${PROJECT_NAME}")

source_group("Headers" FILES ${HEADERSRC})
source_group("Sources" FILES ${CPPSRC})
# add_executable 必须在target_link_libraries之前运行，这样cmake才能找到target。
# 否则，target_link_libraries就会说，${PROJECT_NAME}不是合法的target
add_executable(${PROJECT_NAME} ${CPPSRC} ${HEADERSRC})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLEW_LIB} ${GLFW_LIB} ${SOIL_LIB})
