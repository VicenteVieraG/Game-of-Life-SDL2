find_package(SDL2 CONFIG REQUIRED)
add_library(${EVENTS} STATIC Events.cpp)

target_link_libraries(${EVENTS}
    PRIVATE ${CELL}
    PRIVATE ${GRID}
    PRIVATE SDL2::SDL2
)