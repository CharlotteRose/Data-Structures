#include "Cell.h"
#include <iostream>
#include "CellBoard.h"



void cellTest();
int main(){

    //cellTest();
    CellBoard ourGame("test");


    return 0;
}


void cellTest(){

    //test constructor
    Cell tempCell;
    tempCell.testCell();

    std::cout << "The cell test completed successfully." << std::endl;
}
