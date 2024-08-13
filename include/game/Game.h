#ifndef GAME_H
#define GAME_H

#include <vector>
#include <utility>
#include <SDL2/SDL.h>

#include <Grid.h>
#include <Cell.h>

class Game {
    private:
        SDL_Window* Window;
        SDL_Renderer* Renderer;
        SDL_bool shouldStop;
        const unsigned int WINDOW_WIDTH = 640;
        const unsigned int WINDOW_HEIGHT = 480;
        
        unsigned int population;
        unsigned int generation;
        
        Grid grid;
        std::vector<Cell*> cells;
        std::vector<std::pair<unsigned int, unsigned int>> blocks;

        const unsigned int availableThreads();
        const unsigned int THREADS;
        
        void nextState();
    public:
        Game();
        ~Game();
        
        void menu() const;
        void start();
};

#endif