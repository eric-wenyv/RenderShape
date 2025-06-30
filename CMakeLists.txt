cmake_minimum_required(VERSION 3.10)
project(ConsoleRender)

set(CMAKE_CXX_STANDARD 17)

# 包含头文件目录
include_directories(include)

# 添加源文件
file(GLOB SOURCES src/*.cpp)

add_executable(demo ${SOURCES}
        src/Shape.cpp
        include/Shape.h
        src/renderUtils.cpp
        include/renderUtils.h)