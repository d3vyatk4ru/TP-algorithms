cmake_minimum_required(VERSION 3.21)
project(Task_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Task_1
        ArcGraph.cpp
        ArcGraph.h
        IGraph.h
        ListGraph.cpp
        ListGraph.h
        main.cpp
        MatrixGraph.cpp
        MatrixGraph.h
        SetGraph.cpp
        SetGraph.h)
