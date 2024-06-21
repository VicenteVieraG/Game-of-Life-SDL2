#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SDL2/SDL.h>

#include <Grid.h>
#include <Cell.h>

class Game {
    private:
        SDL_Window* Window;
        SDL_Renderer* Renderer;
        const unsigned int WINDOW_WIDTH = 640;
        const unsigned int WINDOW_HEIGHT = 480;
        SDL_bool shouldStop;
        Grid grid;
        unsigned int population;
        unsigned int generation;
        std::vector<Cell> liveCells;
    public:
        Game();
        void start();
};

#endif