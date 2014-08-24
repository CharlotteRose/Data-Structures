#ifndef CELL_BOARD_H
#define CELL_BOARD_H

#include <vector>
#include <string>
#include "Cell.h"

#define MAX_DISPLAY_WIDTH 25
#define MAX_DISPLAY_HEIGHT 25
#define PRINT_SCREEN 15


class Cell;

class CellBoard{
    public:
        CellBoard(std::string);
        ~CellBoard();

        void checkRules();
        void updateCells();
        void printBoard();
        void checkRowValues(int& y);
        void checkColumnValues(int& x);

        bool errorsDetected();

        void testAllCells();

    private:
        std::vector < std::vector<Cell*> > gameSpace;
        int rows;
        int columns;
        bool readError;


        void checkNeighbors(Cell*&, int y, int x);


        void readGameFile(std::string);



};





#endif // CELL_BOARD_H
