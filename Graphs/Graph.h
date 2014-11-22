#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <string>
#include "Node.h"
#include "PriorityQueue.h"


class Graph{

    public:
        Graph(std::string fileToOpen);
        void initialize(std::string fileToOpen);
        void printGraph();
        void printMatrix();
        void breadthFirst(Node* currentNode);
        void depthFirst(Node* currentNode);
        void testQueue();
        void dijkstra();
        void graveyard(char targetValue);
        void prim();
        void kruskal();
        void testPath(char testValue);
        int testInfPath(char pathValue);

        std::vector <Node*> masterList;
        std::vector <Node*>::iterator it; //iterator to allow access to master list

        std::vector <std::vector <int> > adjacencyMatrix;

        Node* startNode;
        Node* infStartNode;
        int numOfNodes;

        void resetChecks();
        void resetInfChecks();

    private:
        PriorityQueue priorityQueue;
        PriorityQueue infPriorityQueue;

        int timeValue = 0;

        void dijkstra(Node* currentNode, int pathSum);
        bool infCheck(Node* currentNode, char targetValue);
        void infCheck(Node* currentNode, int pathSum);

        void graveyard(Node* currentNode, int pathSum, bool& infTime);

        void prim(Node* currentNode, int edgeWeight);
        void kruskal(Node* currentNode, int edgeWeight);

};

#endif // GRAPH_H
