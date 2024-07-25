#ifndef GRID_H
#define GRID_H

#include <utility>
#include <vector>
#include <memory>
#include <Cell.h>

/*
    @details
        Create a Grid of Cells represented by coords in the following way:
        [x_0][y_0], [x_1][y_0], [x_2][y_0]
        [x_0][y_1], [x_1][y_1], [x_2][y_1]
        [x_0][y_2], [x_1][y_2], [x_2][y_2]
*/
class Grid {
    public:
        Grid() = default;
        Grid(unsigned int cols, unsigned int rows);

        unsigned int cols;
        unsigned int rows;

        Cell minBound;
        Cell maxBound;

        std::vector<std::vector<Cell>> grid;
        std::pair<Cell, Cell> boundingBox;

        void printGrid() const;
        void printStatus() const;

        Cell& at(const Coord coord);
        const Cell& at(const Coord coord) const;
        void setState(const State state, const Coord coord);
        unsigned int countNeighbors(const Cell& cell) const;
};

#endif