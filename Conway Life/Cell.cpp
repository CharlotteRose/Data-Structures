#include <iostream>
#include "Cell.h"
#include <string>

void Cell::updateLiveNeighbors(int newNeighborsAlive){

    if(newNeighborsAlive <0 || newNeighborsAlive > 8){
        std::cout << "ERROR IN COUNTING NEIGHBORS, setting to zero" << std::endl;
        numNeighborsAlive = 0;
    }

    this->numNeighborsAlive = newNeighborsAlive;
}


void Cell::updateCell(){
    if(numNeighborsAlive < 0 || numNeighborsAlive > 8){
        std::cout << "ERROR IN UPDATING NUMBER OF NEIGHBORS, setting to zero" << std::endl;
        numNeighborsAlive = 0;
    }

    if(numNeighborsAlive < 2)
        cellState = cellState->nextState(Dead);
    else if (numNeighborsAlive == 3)
        cellState = cellState->nextState(Alive);
    else if (numNeighborsAlive > 3)
    {
        cellState = cellState->nextState(Dead);
    }
}

void Cell::testCell(){
    bool exit = false;
    std::string stateString = "";

    if(this->cellState->getState() == true)
    {
        stateString = "alive.";
    }
    else{
        stateString = "dead.";
    }

    std::cout << "The default state of a cell is : " << stateString << std::endl;

    while (exit == false){
        std::cout << "Enter a number of neighbors to test (75 to exit) : ";
        std::cin >> numNeighborsAlive;

        std::cout << std::endl << std::endl << std::endl;
        if(numNeighborsAlive == 75)
        {
            exit = true;
        }
        else
        {
            this->updateCell();

            if(this->cellState->getState() == true)
            {
                stateString = "alive.";
            }
            else{
                stateString = "dead.";
            }


            std::cout << "The cell has " << numNeighborsAlive << " neighbors alive and is " << stateString << std::endl;
            std::cout << std::endl;
        }

    }

}

void Cell::initializeLiveCell(){
    cellState = cellState->nextState(Alive);

}

bool Cell::getState(){
    return cellState->getState();
}


int Cell::getNeigh(){
    return numNeighborsAlive;
}
