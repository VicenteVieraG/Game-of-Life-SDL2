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
        for(int j = 0;j < this->grid.cols;j++) this->cells.push_back(&this->grid.at({j, i})); 
    }
}

// Complexity: O()
void Game::nextState(){
    std::vector<std::thread> threads;
    Grid isoGrid = this->grid;
    // std::system("cls");
    // isoGrid.printStatus(this->generation, this->population);

    // Divide the grid in blocks for each available thread
    const unsigned int BLOCK_SIZE = static_cast<unsigned int>(std::ceil(static_cast<double>(this->grid.size) / static_cast<double>(this->THREADS)));

    std::vector<std::pair<unsigned int, unsigned int>> BLOCKS(this->THREADS, std::pair<unsigned int, unsigned int>(0, 0));
    BLOCKS[0] = std::pair<unsigned int, unsigned int>(0, BLOCK_SIZE);
    for(unsigned int i = 1;i < BLOCKS.size();i++){
        BLOCKS[i].first = BLOCKS[i - 1].second + 1;

        // The last block will span through the remaining cells
        (i != (BLOCKS.size() - 1)) ? 
            BLOCKS[i].second = BLOCKS[i].first + BLOCK_SIZE
            :
            BLOCKS[i].second = this->cells.size() - 1;
    }
    // // Compute isoGrid from the current grid for next iteration
    // for(const std::vector<Cell>& col : isoGrid.grid){
    //     for(Cell cell : col){
    //         const Coord position = cell.coord;
    //         isoGrid.at(position).neighbors = this->grid.countAliveNeighbors(this->grid.at(position));
    //         isoGrid.at(position).setNewState();
    //     }
    // }
    
    // // Reset neighbor count
    // for(const std::vector<Cell>& col : isoGrid.grid){
    //     for(Cell cell : col) isoGrid.at(cell.coord).neighbors = 0;
    // }

    // this->grid = isoGrid;
    return;
}

void Game::start(){
    // Rendering loop
    // do{
    //     // Manage events
    //     SDL_Event e;
    //     while(SDL_PollEvent(&e) != 0){
    //         switch(e.type){
    //             case SDL_QUIT:
    //                 this->shouldStop = SDL_TRUE;
    //         }
    //     }
    //     // Draw in screen
    //     SDL_SetRenderDrawColor(this->Renderer, 255, 255, 255, 255);
    //     SDL_RenderClear(this->Renderer);

    //     // Debug
        this->nextState();
    //     std::this_thread::sleep_for(100ms);
    //     SDL_RenderPresent(this->Renderer);
    // }while(!this->shouldStop);

    // // Cleaning objects
    // SDL_DestroyRenderer(this->Renderer);
    // SDL_DestroyWindow(this->Window);

    // SDL_Quit();
    return;
}

Game::~Game(){
    SDL_DestroyRenderer(this->Renderer);
    SDL_DestroyWindow(this->Window);
}
