add_library(${COLORS} STATIC Colors.cpp)

target_link_libraries(${COLORS} PUBLIC ${sdl2})