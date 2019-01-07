cmake_minimum_required(VERSION 3.10)
project(libopencvjs)

set(CMAKE_CXX_STANDARD 11)

SET(OPENCV_INCLUDE
        D:\\SDK\\opencv341\\opencv\\build\\include)

include_directories(${OPENCV_INCLUDE})

add_library(libopencvjs SHARED
        libopencvjs.cpp
        libopencvjs.h
        CPPWrapper.h
        CPPWrapper.cpp
        trackingjsGazeCV.cpp
        )

set_target_properties(libopencvjs PROPERTIES
    PUBLIC_HEADER libopencvjs.h)

