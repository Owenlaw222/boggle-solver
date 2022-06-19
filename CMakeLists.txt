cmake_minimum_required(VERSION 3.10)

project(Boggle-Solver VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(UNIX)
    set(CMAKE_CXX_FLAGS "-g")
endif(UNIX)

add_executable(Boggle-Solver src/main.cpp)