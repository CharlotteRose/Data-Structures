#include "CellBoard.h"
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>


CellBoard::CellBoard(std::string gameFileName){
    rows = 0;
    columns = 0;
    readGameFile(gameFileName);
}

CellBoard::~CellBoard(){

    if(readError != true){
        for (int i = 0; i < rows; i++)
        {
            gameSpace[i].resize(0);
        }
        gameSpace.resize(0);
    }
}

void CellBoard::readGameFile(std::string gameFileName){
    std::fstream readFile;
    readError = false;
    char tempInput = 0;

    readFile.open(gameFileName.c_str());
    if(readFile.is_open())
        {
            readFile >> rows;
            readFile >> columns;

            if(rows > MAX_DISPLAY_HEIGHT || columns > MAX_DISPLAY_WIDTH)
            {
                readError = true;
            }

            if(readError != true)
            {
                gameSpace.resize(rows);
                for(int i = 0; i < rows; i++)
                {
                    gameSpace[i].resize(columns);
                }

                for (int i = 0; i < rows; i++)
                {
                    for(int j = 0; j < columns; j++)
                    {
                        gameSpace[i][j] = new Cell();
                    }
                }


                for(int i = 0; i < rows; i++)
                {
                    for(int j = 0; j < columns; j++)
                    {
                        readFile >> tempInput;
                        if (tempInput == '1')
                        {
                            gameSpace[i][j]->initializeLiveCell();
                        }

                    }
                }

                readFile.close();
            }
            else
                std::cout << "The game file exceeds the map dimensions, please use a valid file." << std::endl;
                readFile.close();
        }
    else
        std::cout << "The file was not found or does not exist." << std::endl;

}

void CellBoard::testAllCells(){

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++){
            std::cout << "Cell (" << i << " , " << j << ") is ";

            if( gameSpace[i][j]->getState() == Alive)
            {
                std::cout << "alive." << std::endl;
            }
            else
                std::cout << "dead." << std::endl;
        }
    }
}

void CellBoard::printBoard(){

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++){
            std::cout << gameSpace[i][j]->getState() << " ";
        }

        std::cout << std::endl;
    }

    for( int i = 0; i < PRINT_SCREEN; i++){
            std::cout << std::endl;
        }

        Sleep(725);
}

void CellBoard::updateCells(){

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++){
            gameSpace[i][j]->updateCell();
        }
    }
}

void CellBoard::checkRules(){

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++){
            checkNeighbors(gameSpace[i][j], i, j);
        }
    }
}


void CellBoard::checkNeighbors(Cell*& currentCell, int y, int x){

    int tempNeighbors = 0;
    bool neighborIsAlive = false;

    //converts cell location to top left neighbor
    int i = y - 1;
    int j = x - 1;

    //wraps around the boundaries before checking
    checkRowValues(i);
    checkColumnValues(j);

    for(int yCount = 0; yCount < 3; yCount++)
    {
        //checks for right wrap
        checkRowValues(i);
        for(int xCount = 0; xCount < 3; xCount++)
        {
            //checks for bottom wrap
            checkColumnValues(j);

            neighborIsAlive = gameSpace[i][j]->getState();
            if(neighborIsAlive == true)
            {
                tempNeighbors++;

            }

            if(tempNeighbors >= 4)
            {
                break;
            }
            j++;
        }
        i++;
        j = x - 1;

        if(tempNeighbors >= 4)
        {
            break;
        }
    }

    currentCell->updateLiveNeighbors(tempNeighbors);
}

void CellBoard::checkRowValues(int& y){
    if( y < 0)
        y = rows - 1;
    if( y > (rows - 1))
        y = 0;
}


void CellBoard::checkColumnValues(int& x){
    if( x > (columns - 1))
        x = 0;
    if( x < 0)
        x = columns - 1;
}


bool CellBoard::errorsDetected(){
    return readError;
}
