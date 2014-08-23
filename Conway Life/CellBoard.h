#ifndef CELL_BOARD_H
#define CELL_BOARD_H

#include <vector>
#include <string>
#include "Cell.h"

#define MAX_DISPLAY_WIDTH 25
#define MAX_DISPLAY_HEIGHT 25

class Cell;

class CellBoard{
    public:
        CellBoard(std::string);
        ~CellBoard();

        void checkRules();
        void updateCells();

    private:
        std::vector < std::vector<Cell> > gameSpace;
        int rows;
        int columns;


        void checkNeighbors(Cell&);


        void readGameFile(std::string);



};





#endif // CELL_BOARD_H
