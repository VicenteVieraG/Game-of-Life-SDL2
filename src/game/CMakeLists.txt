add_library(${GAME} STATIC Game.cpp)

target_link_libraries(${GAME}
    PUBLIC ${GRID}
    PUBLIC ${EVENTS}
    PUBLIC ${COLORS}
    PUBLIC ${sdl2}
)