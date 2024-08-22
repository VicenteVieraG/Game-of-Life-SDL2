#pragma once

#include <utility>
#include <SDL2/SDL.h>

struct Events {
    const SDL_MouseWheelEvent wheel;
    const SDL_WindowEvent window;
};

namespace Handle{
    void stop(SDL_bool& shouldStop);
    void windowEvent(const SDL_WindowEvent& window);
    void wheel(const SDL_MouseWheelEvent wheel, const std::pair<float, float> scale, std::pair<float, float>& offset, std::pair<float, float>& cellSize, float& zoom);
};