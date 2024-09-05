#include <utility>
#include <algorithm>
#include <math.h>

#include <Cell.h>
#include <Events.hpp>
#include <SDL2/SDL.h>

void Handle::stop(){this->shouldStop = SDL_TRUE;}

void Handle::windowEvent(const SDL_WindowEvent& window){
    switch(window.event){
        case SDL_WINDOWEVENT_RESIZED: break;
    }
}

void Handle::click(const SDL_MouseButtonEvent& mouse){
    switch(mouse.button){
        case SDL_BUTTON_MIDDLE:
        case SDL_BUTTON_RIGHT: this->dragging = true; break;
        case SDL_BUTTON_LEFT:{
            const auto [offsetX, offsetY] = this->offset;

            // Compute grid's relative coord
            FCoord gridCoord = {
                (static_cast<float>(mouse.x) - offsetX) / this->zoom,
                (static_cast<float>(mouse.y) - offsetY) / this->zoom
            };

            if(Cell& selectedCell =
                this->grid.at({static_cast<int>(std::floorf(gridCoord.x)), static_cast<int>(std::floorf(gridCoord.y))});
                selectedCell.state == DEAD)
            {selectedCell.state = ALIVE;} else
            {selectedCell.state = DEAD;}
        }
        default: return;
    }
}

void Handle::clickRelease(const SDL_MouseButtonEvent& mouse){
    switch(mouse.button){
        case SDL_BUTTON_MIDDLE:
        case SDL_BUTTON_RIGHT: this->dragging = false; break;
        default: return;
    }
}

void Handle::keyPress(const SDL_KeyboardEvent& key, bool* test){
    switch(key.keysym.sym){
        case SDLK_SPACE: *this->simState = !(*this->simState); break;
        default: return;
    }
}

void Handle::motion(const SDL_MouseMotionEvent& motion){
    const auto [motionX, motionY] = Coord{motion.xrel, motion.yrel};
    auto& [offsetX, offsetY] = this->offset;

    if(this->dragging){
        offsetX += motionX;
        offsetY += motionY;
    }
}

void Handle::wheel(const SDL_MouseWheelEvent wheel){
    auto& [offsetX, offsetY] = this->offset;
    auto& [cellW, cellH] = this->cellSize;
    const auto [scaleDown, scaleUp] = this->scale;
    const auto [mouseX, mouseY] = Coord{wheel.mouseX, wheel.mouseY};
    const auto [wheelX, wheelY] = Coord{wheel.x, wheel.y};
    const int DISPLACE = -15;
    const float MAX_SCALE = 100.0f;
    const float MIN_SCALE = 10.0f;

    /* ~~Zoom computation~~ */
    const float gridX = (mouseX - offsetX) / this->zoom;
    const float gridY = (mouseY - offsetY) / this->zoom;

    if(wheelY > 0){ // Zoom-in
        this->zoom *= scaleUp;
        
        cellW *= scaleUp;
        cellH *= scaleUp;
    }else if(wheelY < 0){ // Zoom-out
        this->zoom *= scaleDown;

        cellW *= scaleDown;
        cellH *= scaleDown;
    }

    // Handle scale boudaries
    this->zoom = std::clamp(this->zoom, MIN_SCALE, MAX_SCALE);
    cellW = std::clamp(cellW, MIN_SCALE, MAX_SCALE); 
    cellH = std::clamp(cellH, MIN_SCALE, MAX_SCALE); 

    // New offset
    offsetX = mouseX - gridX * this->zoom;
    offsetY = mouseY - gridY * this->zoom;

    // Horizontal displace
    if(wheelX) offsetX += static_cast<float>(wheelX * DISPLACE);
}
