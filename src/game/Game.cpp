#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <utility>
#include <thread>
#include <chrono>
#include <SDL2/SDL.h>

#include <Cell.h>
#include <Grid.h>
#include <Game.h>

using namespace std::literals::chrono_literals;

const unsigned int Game::availableThreads(){
    const unsigned int THREADS = std::thread::hardware_concurrency();
    return THREADS ? THREADS : 2U;
}

Game::Game(): generation(0), population(0), shouldStop(SDL_FALSE), THREADS(availableThreads()) {
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr<<"-- Error initializing SDL"<<std::endl;
        std::cout<<"-- SDL Error: "<<SDL_GetError()<<std::endl;
        std::exit(-1);
    }

    this->Window = SDL_CreateWindow(
        "Game of Life",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        this->WINDOW_WIDTH,
        this->WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if(this->Window == nullptr){
        std::cerr<<"-- Error creating Window"<<std::endl;
        std::cout<<"-- SDL Error: "<<SDL_GetError()<<std::endl;

        SDL_Quit();
        std::exit(-1);
    }

    this->Renderer = SDL_CreateRenderer(
        this->Window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if(this->Renderer == nullptr){
        std::cerr<<"-- Error creating Renderer"<<std::endl;
        std::cout<<"-- SDL Error: "<<SDL_GetError()<<std::endl;

        SDL_DestroyWindow(this->Window);
        SDL_Quit();
        std::exit(-1);
    }

    this->grid = Grid(200, 200);
    this->grid.at({80, 80}).state = ALIVE;
    this->grid.at({81, 80}).state = ALIVE;
    this->grid.at({81, 81}).state = ALIVE;
    this->grid.at({82, 81}).state = ALIVE;
    this->grid.at({81, 82}).state = ALIVE;

    // Initialize Game attributes
    for(int i = 0;i < this->grid.rows;i++){
        for(int j = 0;j < this->grid.cols;j++) this->cells.emplace_back(&this->grid.at({j, i}));
    }

    // Divide the grid in blocks for each available thread
    const unsigned int BLOCK_SIZE = static_cast<unsigned int>(std::ceil(static_cast<double>(this->grid.size) / static_cast<double>(this->THREADS)));

    this->blocks = std::vector<std::pair<unsigned int, unsigned int>>(this->THREADS, std::pair<unsigned int, unsigned int>(0, 0));
    this->blocks[0] = std::pair<unsigned int, unsigned int>(0, BLOCK_SIZE);
    for(unsigned int i = 1; i < this->blocks.size();i++){
        auto& [first, last] = this->blocks[i];
        auto [firstPrev, lastPrev] = this->blocks[i - 1];

        first = ++lastPrev;

        // The last block will span through the remaining cells
        (i != (this->blocks.size() - 1)) ? last = first + BLOCK_SIZE : last = this->cells.size() - 1;
    }
}

// Complexity: O()
void Game::nextState(){
    std::vector<std::thread> threads;
    Grid isoGrid = this->grid;
    this->population = 0;
    this->generation++;

    // Create a thread for each block to compute the next generation
    for(const std::pair<unsigned int, unsigned int>& block : this->blocks){
        threads.emplace_back([&](const std::pair<unsigned int, unsigned int>& range) -> void {
            const auto& [first, last] = range;
            for(unsigned int i = first;i <= last;i++){
                const Coord CURRENT = this->cells[i]->coord;

                isoGrid.at(CURRENT).neighbors = this->grid.countAliveNeighbors(CURRENT);
                isoGrid.at(CURRENT).setNewState();
                if(isoGrid.at(CURRENT).state) this->population++;
            }
        }, block);
    }
    for(std::thread& thread : threads) thread.join();

    // Merge the grids to update the state at the same time
    this->grid = isoGrid;

    return;
}

void Game::start(){
    /* ~~Inicialization~~ */
    std::pair<int, int> winSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT); // Window's size
    const std::pair<float, float> scale(0.9f, 1.1f); // Initial scale up/down factor
    std::pair<float, float> cellSize(1.0f, 1.0f);
    const int GAP = 1;

    // Colors
    const auto [rW, gW, bW, aW] = SDL_Color{255, 255, 255, 100};
    const auto [rB, gB, bB, aB] = SDL_Color{0, 0, 0, 100};

    /* ~~Rendering loop~~ */
    do{
        // Manage events
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            switch(e.type){
                case SDL_QUIT:
                    this->shouldStop = SDL_TRUE;
                    break;
                case SDL_WINDOWEVENT:
                    switch(e.window.event){
                        case SDL_WINDOWEVENT_CLOSE:
                            this->shouldStop = SDL_TRUE;
                            break;
                        case SDL_WINDOWEVENT_RESIZED:
                            auto& [width, height] = winSize;
                            SDL_GetWindowSize(this->Window, &width, &height);
                            break;
                    }
            }
        }

        /* ~~Draw in screen~~ */
        this->nextState();

        // Set background to black
        SDL_SetRenderDrawColor(this->Renderer, rW, gW, bW, aW);
        SDL_RenderClear(this->Renderer);

        // Grid Rendering
        for(const std::vector<Cell>& row : this->grid.grid){
            for(const Cell& cell : row){
                const auto& [x, y] = cell.coord;
                const auto& [width, height] = cellSize;

                const SDL_FRect SQUARE = {
                    x + GAP + (width * x),
                    y + GAP + (height * y),
                    width,
                    height
                };

                cell.state ?
                    SDL_SetRenderDrawColor(this->Renderer, rW, gW, bW, aW)
                    :
                    SDL_SetRenderDrawColor(this->Renderer, rB, gB, bB, aB);
                SDL_RenderFillRectF(this->Renderer, &SQUARE);
            }
        }

        SDL_RenderPresent(this->Renderer);
        SDL_Delay(16);
        
        /* ~~Debug terminal print~~ */
        // std::system("cls");
        // this->grid.printStatus(this->generation, this->population);
        // this->nextState();
        // std::this_thread::sleep_for(100ms);
    }while(!this->shouldStop);

    // Cleaning objects
    SDL_DestroyRenderer(this->Renderer);
    SDL_DestroyWindow(this->Window);

    SDL_Quit();
    return;
}

Game::~Game(){
    SDL_DestroyRenderer(this->Renderer);
    SDL_DestroyWindow(this->Window);
}
