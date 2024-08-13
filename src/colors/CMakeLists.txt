add_library(${COLORS} STATIC Colors.cpp)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${COLORS} PUBLIC SDL2::SDL2)