add_library(${GAME} STATIC Game.cpp)

find_package(SDL2 CONFIG REQUIRED)
find_package(imgui CONFIG
    COMPONENTS
        sdl2-binding
        sdl2-renderer-binding
    REQUIRED
)
target_link_libraries(${GAME}
    PUBLIC ${GRID}
    PUBLIC ${EVENTS}
    PUBLIC ${COLORS}
    PUBLIC SDL2::SDL2
    PUBLIC imgui::imgui
)