#include <iostream>
#include <queue>
const int size = 25;

//no ifs

int modNum(int num1, int num2);
void init(bool[][size]);
void run(bool[][size]);


struct Node{
    int xPos;
    int yPos;
    bool nextState;
};

queue<Node*> nodeChanger5000;

int main(){

int i = 0;
bool ary[size][size];
init(ary);



    return 1230;
}

/*
while (condition == true && i < 1) {



    i++
}
*/
int modNum(int num1, int num2) {

    while (num1 > num2) {
        return num1%num2;
    }

    num1 += num2;
    return num1;
}

void init(bool ary[][size]) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            ary[i][j] = false;
        }
    }
}

void run(bool ary[][size]) {
    Node* stateChanger5000;
    int maxNeighbors = 8;
    int neighborsAlive = 0;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            //neighbor check offsets

            int neighborCounter =0; //counts the spaces around the current cell
            while(neighborCounter < maxNeighbors){
            for(int y = -1; y < 2; y++){
                for(int x = -1; x < 2; x++){
                   while( x != 0 && y != 0){
                        neighborCounter++;
                        neighborsAlive += static_cast<int>(ary[modNum(i+y, size)][modNum(j+x, size)]);
                        break;
                    }
                }

            }

            }
            //pushes to our queue if logic check stuffs happen just right

            while(neighborsAlive < 2){
                //push false
                stateChanger5000 = new Node;
                stateChanger5000->xPos = j;
                stateChanger5000->yPos = i;
                stateChanger5000->nextState = false;
                nodeChanger5000.push(stateChanger5000);
                break;
            }

            while(neighborsAlive == 3){
                //push true

                stateChanger5000 = new Node;
                stateChanger5000->xPos = j;
                stateChanger5000->yPos = i;
                stateChanger5000->nextState = true;
                nodeChanger5000.push(stateChanger5000);
                break;
            }

            while(neighborsAlive > 3){
                //push false

                stateChanger5000 = new Node;
                stateChanger5000->xPos = j;
                stateChanger5000->yPos = i;
                stateChanger5000->nextState = false;
                nodeChanger5000.push(stateChanger5000);

                break;
            }
        }
    }

    for (int i = 0; i < nodeChanger5000.size(); i++) {

    }
}
