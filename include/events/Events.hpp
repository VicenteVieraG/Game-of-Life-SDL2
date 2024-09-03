#pragma once
#include <Grid.h>

#include <utility>
#include <SDL2/SDL.h>

struct Events {
    const SDL_WindowEvent window;
    const SDL_MouseButtonEvent mouseBtn;
    const SDL_MouseMotionEvent motion;
    const SDL_MouseWheelEvent wheel;
};

class Handle{
    private:
        SDL_bool& shouldStop;
        bool dragging = false;
        float& zoom;

        Grid& grid;

        const unsigned int GAP;
        const std::pair<float, float>& scale;
        std::pair<float, float>& offset;
        std::pair<float, float>& cellSize;
    public:
        Handle() = default;
        Handle(SDL_bool& shouldStop, float& zoom, const unsigned int GAP, Grid& grid, const std::pair<float, float>& scale, std::pair<float, float>& offset, std::pair<float, float>& cellSize): shouldStop(shouldStop), zoom(zoom), scale(scale), GAP(GAP), grid(grid), offset(offset), cellSize(cellSize){};
        ~Handle() = default;

        void stop();
        void windowEvent(const SDL_WindowEvent& window);
        void click(const SDL_MouseButtonEvent& mouse);
        void clickRelease(const SDL_MouseButtonEvent& mouse);
        void motion(const SDL_MouseMotionEvent& motion);
        void wheel(const SDL_MouseWheelEvent wheel);
};