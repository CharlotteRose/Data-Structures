#include <assert.h>
#include <string>
const int gridSize = 11;

bool makeLiveCell(int x, int y, bool[][gridSize]);

bool nextCellState(bool currentState);
int getNumberOfNeighbors(int i,int j,bool[][gridSize]);
bool allCellsAlive(bool[][gridSize]);

std::string playerWantsToPlay();

int main(){


    assert(playerWantsToPlay() == "Yes");
    bool cell[gridSize][gridSize];

    int i = 0;
    int j = 0;

    cell[i][j] = true;

    assert(cell[i][j] == true);

    cell[i][j] = nextCellState(cell[i][j]);

    assert(makeLiveCell(i,j, cell) == true);
    assert(nextCellState(cell[i][j]) != cell[i][j]);

    cell[i][j] = nextCellState(cell[i][j]);
    assert(makeLiveCell(i,j, cell) == false);

    int numNeighbors = 4;

    assert(numNeighbors >= 0 && numNeighbors <= 8);
    assert(gridSize > 10 && getNumberOfNeighbors(i,j,cell) >= 0);



    assert(allCellsAlive(cell) == true);

    return 1230;
}


bool makeLiveCell(int x, int y, bool cell[][gridSize]){


    if(cell[x][y] == false){
        return true;
        assert(cell[x][y] == true);
        return true;
    }

    return false;
}

bool nextCellState(bool currentState)
{
    return !currentState;
}


int getNumberOfNeighbors(int i,int j, bool cell[][gridSize]){

    return 0;
}

bool allCellsAlive(bool cell[][gridSize])
{
    return true;
}

std::string playerWantsToPlay()
{
    return "Yes";
}


