cmake_minimum_required(VERSION 3.23)
project(DA_Programming_Project_I_main)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(DA_Programming_Project_I_main
        include/config.h
        include/Graph.h
        include/Parser.h
        include/Reviewer.h
        include/Submission.h
        src/Main.cpp
        src/Parser.cpp)
