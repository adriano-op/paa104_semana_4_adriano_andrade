cmake_minimum_required(VERSION 3.19)
project(semana4)

set(CMAKE_CXX_STANDARD 14)

add_executable(semana4 main.cpp)

add_subdirectory (matplotplusplus)

target_link_libraries (semana4 PUBLIC matplot)
