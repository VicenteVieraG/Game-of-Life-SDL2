#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <compare>

// Directions unit vectors for Coords
#define RIGHT {1, 0}
#define LEFT {-1, 0}
#define BOTTOM {0, 1}
#define TOP {0, -1}
#define TOPRIGHT {1, -1}
#define TOPLEFT {-1, -1}
#define BOTTOMRIGHT {1, 1}
#define BOTTOMLEFT {-1, 1}

enum State {
    DEAD,
    ALIVE
};

struct Coord {
    int x = 0;
    int y = 0;
    auto operator<=>(const Coord&) const = default;
    Coord operator+(const Coord& otherCoord) const{return {x + otherCoord.x, y + otherCoord.y};}
    friend std::ostream& operator<<(std::ostream& os, const Coord& coord){
        os<<"{"<<coord.x<<", "<<coord.y<<"}";
        return os;
    }
};

class Cell {
    public:
        Cell() = default;
        Cell(State state, Coord coord) : state(state), coord(coord){this->neighbors = 0;};
        ~Cell() = default;

        State state;
        Coord coord;
        unsigned int neighbors;

        void setNewState();
};

#endif