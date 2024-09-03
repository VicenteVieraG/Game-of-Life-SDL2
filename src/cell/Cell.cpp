#include <Cell.h>

// The cell keeps the same state if it has 2 or 3 neighbors.
// A new cell is born if it has exactly 3 neighbors.
// For the rest of cases the cell dies.
// If it has less than 2 neighbors, the cell dies of solitude.
// If the cell has more than 3 neighbors, the cell dies as if for overpopulation.

void Cell::setNewState() {
    switch(this->neighbors){
        case 2:
        case 3: if(this->neighbors == 3) this->state = ALIVE; break;
        default: this->state = DEAD; break;
    }
}