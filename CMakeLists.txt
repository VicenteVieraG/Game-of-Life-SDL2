cmake_minimum_required(VERSION 3.30.4)

project(GAME_OF_LIFE VERSION 4.1.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}\\bin)

# Libs
set(CELL cell)
set(GRID grid)
set(GAME game)
set(COLORS colors)
set(EVENTS events)
# External
set(sdl2 SDL2)
set(imgui ImGUI)

# Paths
set(SDL2_PATH ${CMAKE_SOURCE_DIR}/external/sdl2/lib/SDL2.dll)
set(SDL2_IMPORT_PATH ${CMAKE_SOURCE_DIR}/external/sdl2/lib/SDL2.lib)

# Includes
set(SDL2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/sdl2/include/)

# Subdirectories
add_subdirectory(config)
add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(app)