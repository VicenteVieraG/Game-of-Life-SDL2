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
    if(coord.x >= this->cols || coord.y >= this->rows ) throw std::out_of_range("-- Out of range grid's coord access at Cell& Grid::at D:");
    return this->grid[coord.y][coord.x];
}
const Cell& Grid::at(const Coord coord) const {
    if(coord.x >= this->cols || coord.y >= this->rows) throw std::out_of_range("-- Out of range grid's coord access at cosnt Cell& Grid::at const D:");
    return this->grid[coord.y][coord.x];
}

// @deprecated
void Grid::setState(const State state, const Coord coord){
    try{
        if(this->grid.empty()) throw std::runtime_error("-- Can not set state of an empty grid D:");
        if(coord.x >= this->cols || coord.y >= this->rows) throw std::out_of_range("-- Out of range cell. The values must be within the colums and rows range.");

        // at(coord).state = state;
        this->at(coord).state = state;

        return;
    }catch(const std::exception& e){
        std::cerr<<e.what()<<std::endl;
        std::cerr<<"The given coords values are: "<<"[x: "<<coord.x<<", y: "<<coord.y<<"]"<<std::endl;
        std::cerr<<"The ranges of the grid are: "<<"[x: "<<this->cols<<", y: "<<this->rows<<"]"<<std::endl;
        return;
    }
}

unsigned int Grid::countAliveNeighbors(const Coord coord) const{
    // Directions to lookup for alive neighbors
    const Coord NULL_COORD = {-1, -1};
    const Coord BOUND_COORD = {(int)this->cols, (int)this->rows};
    unsigned int count = 0;

    for(const Coord& direction : directions){
        const Coord neighborCoord = coord + direction;
        if(neighborCoord != NULL_COORD &&
           neighborCoord.x < this->cols - 1 && neighborCoord.y < this->rows){
            if(this->at(neighborCoord).state) count++;
        }
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