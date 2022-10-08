cmake_minimum_required(VERSION 3.10)

project(boggle-solver VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

add_executable(${PROJECT_NAME} src/main.cpp
                               src/solver/board.cpp
                               src/solver/solver.cpp
                               src/interface/main_interface.cpp)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(GTK REQUIRED gtk+-3.0)
PKG_SEARCH_MODULE(GTKMM REQUIRED gtkmm-3.0)

INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${GTK3_LIBRARIES} ${GTKMM_LIBRARIES})