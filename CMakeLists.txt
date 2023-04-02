cmake_minimum_required(VERSION 3.5)

project(Kursach2022_THIS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Kursach2022_THIS main.cpp)

set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")
target_link_libraries(Kursach2022_THIS sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5.1 REQUIRED graphics network audio window system)


