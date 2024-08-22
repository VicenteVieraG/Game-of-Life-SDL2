#include <utility>

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

    void wheel(const SDL_MouseWheelEvent wheel, const std::pair<float, float> scale, std::pair<float, float>& offset, std::pair<float, float>& cellSize, float& zoom){
        auto& [offsetX, offsetY] = offset;
        auto& [cellW, cellH] = cellSize;
        const auto [scaleDown, scaleUp] = scale;
        const auto [mouseX, mouseY] = Coord{wheel.mouseX, wheel.mouseY};
        const auto [wheelX, wheelY] = Coord{wheel.x, wheel.y};
        const int displace = -15;

        /* ~~Zoom computation~~ */
        const float gridX = (mouseX - offsetX) / zoom;
        const float gridY = (mouseY - offsetY) / zoom;

        if(wheelY > 0) zoom *= scaleUp;
        if(wheelY < 0) zoom *= scaleDown;

        // New offset
        offsetX = mouseX - gridX * zoom;
        offsetY = mouseY - gridY * zoom;

        // Scale cells' size
        cellW = 1.0f * zoom;
        cellH = 1.0f * zoom;

        // Horizontal displace
        if(wheelX) offsetX += static_cast<float>(wheelX * displace);
    }

};
