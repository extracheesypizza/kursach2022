cmake_minimum_required(VERSION 3.5)

project(Kursach2022 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Kursach2022 main.cpp AVLTree.h Node.h Application.h Controller.h Viewer.h arial.ttf)

set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")
target_link_libraries(Kursach2022 sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5.1 REQUIRED graphics network audio window system)


