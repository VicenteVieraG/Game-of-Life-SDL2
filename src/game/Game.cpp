#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>

#include <Game.h>

Game::Game(){
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

    this->shouldStop = SDL_FALSE;
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

        SDL_RenderPresent(this->Renderer);
    }while(!this->shouldStop);

    // Cleaning objects
    SDL_DestroyRenderer(this->Renderer);
    SDL_DestroyWindow(this->Window);

    SDL_Quit();
    return;
}
