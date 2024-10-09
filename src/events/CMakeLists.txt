add_library(${EVENTS} STATIC Events.cpp)

target_link_libraries(${EVENTS}
    PRIVATE ${CELL}
    PRIVATE ${GRID}
    PRIVATE ${sdl2}
)