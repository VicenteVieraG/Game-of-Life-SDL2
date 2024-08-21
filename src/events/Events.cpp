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

    void wheel(const SDL_MouseWheelEvent wheel, const std::pair<float, float> scale, std::pair<float, float>& offset, std::pair<float, float>& cellSize){
        const auto [mouseX, mouseY] = Coord{wheel.mouseX, wheel.mouseY};
        const auto [x, y] = Coord{wheel.x, wheel.y};
        const auto [scaleUp, scaleDown] = scale;
        auto& [offsetX, offsetY] = offset;
        auto& [cellW, cellH] = cellSize;
        const int displace = 15;

        // Horizontal scroll
        if(x) offsetX += static_cast<float>(x * displace * -1);

        // Vertical Wheel movement
        // if(y > 0){
        //     // offsetW -= this->zoomFactor * (mouseX - offsetW);
        //     // offsetH -= this->zoomFactor * (mouseY - offsetH);

        //     cellW *= scaleUp;
        //     cellH *= scaleUp;

        //     offsetW -= (cellW * scaleUp) - mouseX;
        //     offsetH -= (cellH * scaleUp) - mouseY;
        // }
        // else if(y < 0){
        //     offsetW += this->zoomFactor * (mouseX - offsetW);
        //     offsetH += this->zoomFactor * (mouseY - offsetH);

        //     cellW *= scaleDown;
        //     cellH *= scaleDown;
        // }
    }
};
