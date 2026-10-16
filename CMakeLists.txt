cmake_minimum_required(VERSION 3.20)

project(history-game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(history-game
    src/main.cpp
    src/modifierParser.cpp
)

target_include_directories(history-game PRIVATE include)