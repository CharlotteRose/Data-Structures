#include "CellBoard.h"
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>


CellBoard::CellBoard(){
    std::string gameFileName = "";

    std::cout << "Type the name of the game file and press enter. " << std::endl;
    std::cout << "Game File: ";
    std::cin >> gameFileName;

    generations = 0;
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

    std::cout << "GAME FILE NAME IS: " << gameFileName << std::endl;
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
            {
                std::cout << "The game file exceeds the map dimensions, please use a valid file." << std::endl;
                readError = true;
            }
                readFile.close();
        }
    else
    {
        std::cout << "The file was not found or does not exist." << std::endl;
        readError = true;
    }

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

    generations++;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++){
            std::cout << gameSpace[i][j]->getState() << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl << std::endl << "Number of Generations: " << generations << std::endl << std::endl
              << std::endl << std::endl;

    for( int i = 0; i < PRINT_SCREEN - rows; i++){
            std::cout << std::endl;
        }

        Sleep(625);
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

    if(currentCell->getState() == Alive)
    {
        tempNeighbors--;
    }

    for(int yCount = 0; yCount < 3; yCount++)
    {
        //checks for right wrap
        checkRowValues(i);
        for(int xCount = 0; xCount < 3; xCount++)
        {
            //checks for bottom wrap
            checkColumnValues(j);
            neighborIsAlive = false;
            neighborIsAlive = gameSpace[i][j]->getState();



            if(neighborIsAlive == true)
            {
                //Algorithm was counting current cell as a neighbor.
                //When tried to skip current cell, counts acted odd
                //So this If block corrects the counts.
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
