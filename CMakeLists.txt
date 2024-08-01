# CMake 3.* necessario per Qt
cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

set(project_name "ChessConsole")

project(${project_name})

set(CMAKE_CXX_STANDARD 17)

# ottengo tutti i sorgenti
file(GLOB my_sources src/*.h src/*.cpp)

# aggiungo eseguibile
add_executable(${project_name} ${my_sources})

file(COPY file DESTINATION ${CMAKE_BINARY_DIR})