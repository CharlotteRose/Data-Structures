#ifndef CELL_H
#define CELL_H
#include <stddef.h> //to set object pointer to NULL

enum cellStates{
    Dead,
    Alive
};

class Cell{
    public:
        Cell(){
            numNeighborsAlive = 0;
                cellState = new DeadState;
        };

        ~Cell(){

            if(cellState != NULL)
            {
                delete cellState;
                cellState = NULL;
            }
        };


        //need to complete
        void updateLiveNeighbors(int neighborsAlive);
        void updateCell();
        bool getState();

        int getNeigh();

        void initializeLiveCell();
        void testCell();




    private:

        int numNeighborsAlive;

         class State{
            public:
           virtual State* nextState(bool alive) = 0;
           virtual bool getState() = 0;

            protected:
                bool isAlive;
        };


        class AliveState : public State{
            public:
                AliveState(){
                    isAlive = true;
                }

                State* nextState(bool alive){
                    if (alive == true)
                        return this;
                    else
                        return new DeadState();
                }

                bool getState(){
                    return isAlive;
                }

        };


        class DeadState : public State{
            public:
                DeadState(){
                    isAlive = false;
                }

                State* nextState(bool alive){
                    if (alive == true)
                        return new AliveState();
                    else
                        return this;
                }

                bool getState(){
                    return isAlive;
                }

        };

        State* cellState;

};


#endif // CELL_H
