#include <Cell.h>

void Cell::setCurrentState() {
    // A new cell is born
    if(this->neighbors == 3){
        this->state = ALIVE;
        return;
    }

    // The cell stays alive
    if((this->neighbors == 2 || this->neighbors == 3) && this->state == ALIVE) this->state = ALIVE;
    
    // The cell dies:
    // Overpopulation         Solitude
    if(this->neighbors > 3 || this->neighbors < 2){
        this->state = DEAD;
        return;
    }
}