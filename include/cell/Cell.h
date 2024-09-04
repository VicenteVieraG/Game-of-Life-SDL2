#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <compare>

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

struct FCoord {
    float x = 0.0f;
    float y = 0.0f;
    auto operator<=>(const FCoord&) const = default;
    friend std::ostream& operator<<(std::ostream& os, const FCoord& coord){
        const auto [x, y] = coord;
        os<<"<"<<x<<", "<<y<<">";
        return os;
    }
    // Coord-scalar operations
    auto operator+(const float& other){
        this->x += other;
        this->y += other;
    }
    auto operator-(const float& other){
        this->x -= other;
        this->y -= other;
    }
    // Coord operations
    auto operator-(const FCoord& other){
        this->x -= other.x;
        this->y -= other.y;
    }
};

// Directions unit vectors for Coords
const Coord RIGHT = {1, 0};
const Coord LEFT = {-1, 0};
const Coord BOTTOM = {0, 1};
const Coord TOP = {0, -1};
const Coord TOPRIGHT = TOP + RIGHT;
const Coord TOPLEFT = TOP + LEFT;
const Coord BOTTOMRIGHT = BOTTOM + RIGHT;
const Coord BOTTOMLEFT = BOTTOM + LEFT;
const Coord directions[8] = {RIGHT, LEFT, TOP, BOTTOM, TOPRIGHT, TOPLEFT, BOTTOMRIGHT, BOTTOMLEFT};

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