#include <assert.h>
#include "cell.h"

const int max_size = 4;

bool createLiveCell(int x, int y);
bool replaceDeadCell(int x,int y);
bool changeCellState(int x, int y, int cellArray[][]);
int main(){

    int x = 0;
    int y = 0;
    int cellArray[max_size][max_size];

    Cell changeCell;

    for(int i = 0; i < max_size; i++)
    {

        for(int j = 0; j < max_size: j++)
        {

            cellArray[i][j] = changeCell.cellBoard[i][j];

        }// for(int j = 0; j < max_size: j++)

    }// for(int i = 0; i < max_size; i++)

    assert(createLiveCell(x, y) == true);

    assert(replaceDeadCell(x,y) == false);


    assert(changeCellState(x, y, cellArray) == true);

    std::cout << "end" << std::endl;

}

bool createLiveCell(int x, int y)
{
    Cell eachCell;

    return eachCell.createLiveCell(x, y);


}// bool createLiveCell(int x, int y)

bool replaceDeadCell(int x, int y){


    return false;
}

bool changeCellState(int x, int y, int cellArray[][])
{



    return true;

}// bool changeCellState(int x, int y, int cellArray[][])
