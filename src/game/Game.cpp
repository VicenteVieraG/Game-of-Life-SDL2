#include <iostream>
#include <stdio.h>
#include <vector>
#include <thread>
#include <algorithm>
#include <chrono>
#include <SDL2/SDL.h>

#include <Cell.h>
#include <Grid.h>
#include <Game.h>

using namespace std::literals::chrono_literals;

const unsigned int availableThreads(){
    const unsigned int THREADS = std::thread::hardware_concurrency();
    return THREADS ? THREADS : 2U;
}
const unsigned int THREADS = availableThreads();

Game::Game() {
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
        this->WINDOW_WIDTH,
        SDL_WINDOW_SHOWN
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
        for(int j =0;j < this->grid.cols;j++) this->cells.push_back(&this->grid.at({j, i})); 
    }

    this->shouldStop = SDL_FALSE;
    this->population = 0;
    this->generation = 0;
}

// Complexity: O()
void Game::nextState(){
    Grid isoGrid = this->grid;
    std::system("cls");
    isoGrid.printStatus(this->generation, this->population);

    // Compute isoGrid from the current grid for next iteration
    for(const std::vector<Cell>& col : isoGrid.grid){
        for(Cell cell : col){
            const Coord position = cell.coord;
            isoGrid.at(position).neighbors = this->grid.countAliveNeighbors(this->grid.at(position));
            isoGrid.at(position).setNewState();
        }
    }
    
    // Reset neighbor count
    for(const std::vector<Cell>& col : isoGrid.grid){
        for(Cell cell : col) isoGrid.at(cell.coord).neighbors = 0;
    }

    this->grid = isoGrid;
    return;
}

void Game::start(){
    // Rendering loop
    do{
        // Manage events
        SDL_Event e;
        while(SDL_PollEvent(&e) != 0){
            switch(e.type){
                case SDL_QUIT:
                    this->shouldStop = SDL_TRUE;
            }
        }
        // Draw in screen
        SDL_SetRenderDrawColor(this->Renderer, 255, 255, 255, 255);
        SDL_RenderClear(this->Renderer);

        // Debug
        this->nextState();
        std::this_thread::sleep_for(100ms);
        SDL_RenderPresent(this->Renderer);
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
