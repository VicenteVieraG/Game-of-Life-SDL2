#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class Game {
    private:
        SDL_Window* Window;
        SDL_Renderer* Renderer;
        const unsigned int WINDOW_WIDTH = 640;
        const unsigned int WINDOW_HEIGHT = 480;
        SDL_bool shouldStop;
    public:
        Game();
        void start();
};

#endif