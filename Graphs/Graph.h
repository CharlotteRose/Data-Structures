#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <string>
#include "Node.h"


class Graph{

    public:
        Graph();
        void initialize(std::string);
        void printGraph();
        std::vector <Node*> masterList;
        std::vector <Node*>::iterator it; //iterator to allow access to master list

        Node* startNode;
        int numOfNodes;
};

#endif // GRAPH_H
