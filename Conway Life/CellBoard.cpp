#include "CellBoard.h"
#include <string>
#include <fstream>
#include <iostream>



CellBoard::CellBoard(std::string gameFileName){
    rows = 0;
    columns = 0;
    readGameFile(gameFileName);
}

CellBoard::~CellBoard(){
    for (int i = 0; i < rows; i++)
    {
        gameSpace[i].resize(0);
    }

    gameSpace.resize(0);
}

void CellBoard::readGameFile(std::string gameFileName){
    std::fstream readFile;
    bool readError = false;

    readFile.open(gameFileName.c_str());
    if(readFile.is_open())
        {

            while(readFile.eof() != true && readError == false)
            {

            }
        }
    else
        std::cout << "The file was not found or does not exist." << std::endl;

    }
