#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <cstdlib>
#include <ctime>

const int max_size = 4;

class Cell
{
    public:
        Cell();
        bool createLiveCell(int, int);
        void setCellRow(int);
        void setCellCol(int);
        int cellBoard [max_size][max_size];

};
Cell::Cell()
{

    srand(time(NULL));

    for(int i = 0; i < max_size; i++)
    {

        for(int j = 0; j < max_size; j++)
        {

            cellBoard[i][j] = rand() % 1;

        }// for(int j = 0; j < 4; j++)

    }// for(int i = 0; i < 4; i++)

}// Cell::Cell()

bool Cell::createLiveCell(int cellRow, int cellCol)
{
    assert(cellRow < max_size || cellRow > 0 ||
           cellCol < max_size || cellRow > 0);

    if(cellBoard[cellRow][cellCol] == 0)
    {

        return true;

    }// if(cellBoard[cellRow][cellCol] == 1)

    return false;

}// bool Cell::createLiveCell(int cellRow, int cellCol)

#endif // CELL_H
