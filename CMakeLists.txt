cmake_minimum_required(VERSION 3.30.1)

project(GAME_OF_LIFE VERSION 3.4.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}\\bin)

# Libs
set(CELL cell)
set(GRID grid)
set(GAME game)
set(COLORS colors)
set(EVENTS events)

# Subdirectories
add_subdirectory(config)
add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(app)