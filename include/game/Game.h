#ifndef GAME_H
#define GAME_H

#include <vector>
#include <utility>
#include <SDL2/SDL.h>

#include <Grid.h>
#include <Cell.h>
#include <Events.hpp>

class Game {
    private:
        SDL_Window* Window;
        SDL_Renderer* Renderer;
        SDL_bool shouldStop;
        bool simulationState;
        Handle Handle;
        const unsigned int WINDOW_WIDTH = 640;
        const unsigned int WINDOW_HEIGHT = 480;

        std::pair<int, int> winSize;
        std::pair<float, float> cellSize;
        const std::pair<float, float> scale{0.9f, 1.1f};
        std::pair<float, float> offset{0.0f, 0.0f};
        const unsigned int GAP = 1;
        float zoomFactor = 10.0f;
        
        unsigned int population;
        unsigned int generation;
        
        Grid grid;
        std::vector<Cell*> cells;
        std::vector<std::pair<unsigned int, unsigned int>> blocks;

        const unsigned int availableThreads();
        const unsigned int THREADS;
        
        void nextState();
        void renderGrid() const;
    public:
        Game();
        ~Game();
        
        void start();
};

#endif