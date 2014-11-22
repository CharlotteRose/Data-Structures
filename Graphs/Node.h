#ifndef NODE_H
#define NODE_H
#include <vector>


class Node{
public:
    Node(char newValue);

    void addAdjacent(Node*);
    void removeAdjacent(Node*);
    void printNode();

    std::vector <Node*> adjacentList; //contains all adjacent nodes
    std::vector <Node*>::iterator it; //iterator to allow access to adjacent nodes


    char letter;
    std::vector <int> weight;

    int pathSum;
    int infPathSum;

    Node* priorNode;
    Node* infPriorNode;
    int nodeNumber;
    bool isVisited;
    bool infTimeCheck;
};

#endif // NODE_H
