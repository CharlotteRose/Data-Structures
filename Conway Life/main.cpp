#include "Cell.h"
#include <iostream>
#include "CellBoard.h"



void cellTest();
void boardTest();

int main(){

    //cellTest();
    //boardTest();

    CellBoard ourGame("test.txt");
    while(ourGame.errorsDetected() != true)
    {
        ourGame.printBoard();
        ourGame.checkRules();
        ourGame.updateCells();
    }


    return 0;
}


void cellTest(){

    //test constructor
    Cell tempCell;
    tempCell.testCell();

    std::cout << "The cell test completed successfully." << std::endl;
}

void boardTest(){
    CellBoard ourGame("test.txt");
    ourGame.testAllCells();
}
