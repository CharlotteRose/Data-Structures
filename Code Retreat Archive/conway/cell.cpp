#include "cell.h"
#include <vector>

Cell::Cell(bool isAlive){

    if(isAlive){
        currentState = ALIVE;
    }else{
        currentState = DEAD;
    }
};


void Cell::checkNeighbors(){
    int numLiveNeighbors = neighborsAlive();

    if(numLiveNeighbors < 2){
        //lonely
        nextState = DEAD;
    }else if(numLiveNeighbors == 3){
        //rebirth
        nextState = ALIVE;
    }else if(numLiveNeighbors > 3){
        //they eat each other
        nextState = DEAD;
    }


}

void Cell::checkNeighbors(int numTestNeighbor){

    if(numTestNeighbors < 2){
        //lonely
        nextState = DEAD;
    }else if(numTestNeighbors == 3){
        //rebirth
        nextState = ALIVE;
    }else if(numTestNeighbors > 3){
        //they eat each other
        nextState = DEAD;
    }

}


void Cell::updateCell(){
    currentState = nextState;
}


void Cell::addNeighbor(Cell* newNeighbor){
    if(neighborList.size() < maxNeighbors){
        neighborList.push_back(newNeighbor);
    }
}


int Cell::neighborsAlive(){
    std::vector <Cell*> iterator it;
    int i = 0;
    int numAliveNeighbors = 0;

    for(it = neighborList.begin(); it < neighborList.end(); it++, i++){
        if(neighborList[i]->isAlive){
            numAliveNeighbors++;
        };
    }

    return numAliveNeighbors;
}


void Cell::testCell(){

    currentState = ALIVE;


    for(int i = 0; i < 8; i++){
        checkNeighbors(i);
        if(currentState == ALIVE){
            std::cout << "ALIVE" << std::endl;
        }else{
            std::cout << "DEAD" << std::endl;
        }

    }
}
