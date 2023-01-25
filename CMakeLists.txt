cmake_minimum_required(VERSION 3.5)

project(Kursach2022 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Kursach2022 main.cpp AVLTree.h Node.h Application.h Cases.h Controller.h Viewer.h)
