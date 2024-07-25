#include <iostream>
#include <config.hpp>

#define SDL_MAIN_HANDLED
#include <Game.h>

int main(int argc, char** argv){
    std::cout<<project_name<<std::endl;
    std::cout<<project_version<<std::endl;

    Game Life;
    // Life.start();

    return 0;
}