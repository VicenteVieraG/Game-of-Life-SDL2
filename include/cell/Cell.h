#ifndef CELL_H
#define CELL_H

enum State {
    DEAD,
    ALIVE
};

struct Coord {
    unsigned int x = 0;
    unsigned int y = 0;
};

class Cell {
    public:
        Cell() = default;
        Cell(State state, Coord coord, unsigned int neighbors) : state(state), coord(coord), neighbors(neighbors){};
        State state;
        Coord coord;
        unsigned int neighbors;
};

#endif