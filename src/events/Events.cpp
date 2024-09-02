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
        const int DISPLACE = -15;
        const float MAX_SCALE = 100.0f;
        const float MIN_SCALE = 10.0f;

        /* ~~Zoom computation~~ */
        const float gridX = (mouseX - offsetX) / zoom;
        const float gridY = (mouseY - offsetY) / zoom;

        if(wheelY > 0){ // Zoom-in
            zoom *= scaleUp;
            
            cellW *= scaleUp;
            cellH *= scaleUp;
        }else if(wheelY < 0){ // Zoom-out
            zoom *= scaleDown;

            cellW *= scaleDown;
            cellH *= scaleDown;
        }

        // Handle scale boudaries
        zoom = std::clamp(zoom, MIN_SCALE, MAX_SCALE);
        cellW = std::clamp(cellW, MIN_SCALE, MAX_SCALE); 
        cellH = std::clamp(cellH, MIN_SCALE, MAX_SCALE); 

        // New offset
        offsetX = mouseX - gridX * zoom;
        offsetY = mouseY - gridY * zoom;

        // Horizontal displace
        if(wheelX) offsetX += static_cast<float>(wheelX * DISPLACE);
    }
};
