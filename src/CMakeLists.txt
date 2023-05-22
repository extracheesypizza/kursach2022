cmake_minimum_required(VERSION 3.5)

project(Kursach2022 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Kursach2022 main.cpp Application.cpp AVLTree.cpp Controller.cpp Node.cpp Viewer.cpp)
FILE(COPY ../res/arial.ttf DESTINATION "${CMAKE_BINARY_DIR}")

FILE(GLOB_RECURSE LibFiles "*.hpp")
add_custom_target(headers SOURCES ${LibFiles})

target_link_libraries(Kursach2022 sfml-graphics)

#set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
include_directories(${CMAKE_CURRENT_LIST_DIR}/SFML/include)
target_link_libraries(Kursach2022 ${CMAKE_CURRENT_LIST_DIR}/SFML/lib)

find_package(SFML REQUIRED graphics network audio window system)


