#include <iostream>
#include <vector>

#include <Cell.h>
#include <Grid.h>

Grid::Grid(unsigned int cols, unsigned int rows) : cols(cols), rows(rows), grid(rows, std::vector<Cell>(cols)){
    for(unsigned int i = 0;i < this->grid.size();i++){
        for(unsigned int j = 0;j < this->grid[i].size();j++) this->grid[i][j].coord = {i, j};
    }
}

unsigned int Grid::countNeighbors(const Cell& cell) const{
    // if(this->grid[cell.coord.x][cell.coord.y])
}

void Grid::printGrid() const{
    for(const std::vector<Cell>& row : this->grid){
        std::cout<<"| ";
        for(const Cell& cell : row){
            std::cout<<"["<<cell.coord.x<<", "<<cell.coord.y<<"], ";
        }
        std::cout<<"|"<<std::endl;
    }
}

void Grid::printStatus() const{
    for(const std::vector<Cell>& row : this->grid){
        std::cout<<"| ";
        for(const Cell& cell : row){
            std::cout<<cell.state<<" ";
        }
        std::cout<<"|"<<std::endl;
    }
}