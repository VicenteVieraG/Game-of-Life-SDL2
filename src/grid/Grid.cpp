#include <iostream>
#include <string>
#include <vector>
#include <exception>

#include <Cell.h>
#include <Grid.h>

Grid::Grid(unsigned int cols, unsigned int rows) : cols(cols), rows(rows), grid(rows, std::vector<Cell>(cols)){
    // Initialize Cell's coords
    for(unsigned int i = 0;i < this->grid.size();i++){
        for(unsigned int j = 0;j < this->grid[i].size();j++) this->grid[i][j].coord = {(int)j, (int)i};
    }
}

// Retrieves the Grid's Cell at the given Coord
Cell& Grid::at(const Coord coord){
    if(const auto& [x, y] = coord;
        x < 0 && y < 0 &&
        x >= this->cols && y >= this->rows) throw std::out_of_range("-- Out of range grid's coord access at Cell& Grid::at D:");
    return this->grid[coord.y][coord.x];
}
const Cell& Grid::at(const Coord coord) const {
    if(const auto& [x, y] = coord;
        x < 0 && y < 0 &&
        x >= this->cols && y >= this->rows) throw std::out_of_range("-- Out of range grid's coord access at cosnt Cell& Grid::at const D:");
    return this->grid[coord.y][coord.x];
}

unsigned int Grid::countAliveNeighbors(const Coord coord) const{
    unsigned int count = 0;

    for(const Coord& direction : directions){
        if(const auto [x, y] = coord + direction;
            x >= 0 && y >= 0 &&
            x < this->cols && y < this->rows &&
            this->at({x, y}).state == ALIVE
        ) count++;
    }

    return count;
}

void Grid::printGrid() const{
    if(this->grid.empty()){
        std::cerr<<"-- Can not print an empty grid D:"<<std::endl;
        return;
    }

    std::cout<<"-- Position Grid"<<std::endl;

    for(const std::vector<Cell>& row : this->grid){
        std::cout<<"| ";
        for(const Cell& cell : row){
            std::cout<<"["<<cell.coord.x<<", "<<cell.coord.y<<"], ";
        }
        std::cout<<"|"<<std::endl;
    }
}

void Grid::printStatus(const unsigned int& generation, const unsigned int& population) const{
    if(this->grid.empty()){
        std::cerr<<"-- Can not print the status grid if it is empty D:"<<std::endl;
        return;
    }

    std::string outputBuff = "";

    for(const std::vector<Cell>& row : this->grid){
        outputBuff += "| ";
        for(const Cell& cell : row) cell.state ? outputBuff += "0 " : outputBuff += "` ";
        outputBuff += "|\n";
    }
    std::cout
    <<"-- Status\n"
    <<"---- Generation: "<<generation<<"\n"
    <<"---- Population: "<<population<<std::endl;
    std::cout<<outputBuff;
}

void Grid::printNeighbors() const{
    std::cout<<"-- Neighbors print"<<std::endl;
    for(const std::vector<Cell>& col : this->grid){
        std::cout<<"| ";
        for(const Cell& cell : col){
            std::cout<<cell.neighbors<<" ";
        }
        std::cout<<"|"<<std::endl;
    }
}