set(IMGUI_SOURCES imgui.cpp imgui_impl_sdl2.cpp imgui_impl_sdlrenderer2.cpp)

add_library(${imgui} STATIC ${IMGUI_SOURCES})

target_link_libraries(${imgui} PRIVATE ${sdl2})