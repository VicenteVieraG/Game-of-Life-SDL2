add_library(${GAME} STATIC Game.cpp)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${GAME}
    PRIVATE ${CELL}
    PRIVATE ${GRID}
    PUBLIC SDL2::SDL2
)