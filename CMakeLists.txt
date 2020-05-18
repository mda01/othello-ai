cmake_minimum_required(VERSION 3.15)
project(othello)

set(CMAKE_CXX_STANDARD 14)

add_executable(othello main.cpp Board.cpp Board.h MinMax.cpp MinMax.h UI.cpp UI.h)