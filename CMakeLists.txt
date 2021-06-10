cmake_minimum_required(VERSION 3.16)
project(WanderingClouds VERSION 0.0.1)

set(CMAKE_CXXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -fconcepts")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

file(GLOB_RECURSE HEADERS include/*.h)
file(GLOB_RECURSE SOURCES src/*.cc)

file(GLOB_RECURSE VENDOR_HEADERS vendor/include/*.h)
file(GLOB_RECURSE VENDOR_SOURCES vendor/src/*.cc vendor/src/*.c)

include_directories(vendor/include)

add_executable(${PROJECT_NAME} ${VENDOR_HEADERS} ${VENDOR_SOURCES} ${INCLUDES} ${SOURCES} main.cc)

target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw -lX11 -ldl)
