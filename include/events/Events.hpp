#pragma once

#include <utility>
#include <SDL2/SDL.h>

struct Events {
    const SDL_WindowEvent window;
    const SDL_MouseButtonEvent mouseBtn;
    const SDL_MouseWheelEvent wheel;
};

namespace Handle{
    void stop(SDL_bool& shouldStop);
    void windowEvent(const SDL_WindowEvent& window);
    void click(const SDL_MouseButtonEvent& mouse);
    void wheel(const SDL_MouseWheelEvent wheel, const std::pair<float, float> scale, std::pair<float, float>& offset, std::pair<float, float>& cellSize, float& zoom);
};