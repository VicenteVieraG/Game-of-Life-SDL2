#include <utility>
#include <algorithm>

#include <Cell.h>
#include <Events.hpp>
#include <SDL2/SDL.h>

namespace Handle{
    void stop(SDL_bool& shouldStop){shouldStop = SDL_TRUE;}

    void windowEvent(const SDL_WindowEvent& window){
        switch(window.event){
            case SDL_WINDOWEVENT_RESIZED: break;
        }
    }

    void click(const SDL_MouseButtonEvent& mouse){
        switch(mouse.button){
            case SDL_BUTTON_LEFT: break; // Change cell's state
            case SDL_BUTTON_MIDDLE: break; // Drag screen
        }
    }

    void wheel(const SDL_MouseWheelEvent wheel, const std::pair<float, float> scale, std::pair<float, float>& offset, std::pair<float, float>& cellSize, float& zoom){
        auto& [offsetX, offsetY] = offset;
        auto& [cellW, cellH] = cellSize;
        const auto [scaleDown, scaleUp] = scale;
        const auto [mouseX, mouseY] = Coord{wheel.mouseX, wheel.mouseY};
        const auto [wheelX, wheelY] = Coord{wheel.x, wheel.y};
    }
};
