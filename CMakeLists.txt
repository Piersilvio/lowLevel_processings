cmake_minimum_required(VERSION 3.31)
project(lowLevel_processings)

set(CMAKE_CXX_STANDARD 23)

set(ENV{OPENCV_DIR} "C:\\tools\\opencv\\build")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(lowLevel_processings main.cpp
        cmake-build-debug/ImageProcessor.cpp
        cmake-build-debug/ImageProcessor.h
        GUI.cpp
        GUI.h
        ImageProcessor.cpp
        ImageProcessor.h
        PixelOperations.cpp
        PixelOperations.h
        Filters.cpp
        Filters.h)

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

target_link_libraries(lowLevel_processings ${OpenCV_LIBS})