#include "Graph.h"



int main(){
    Graph testGraph("Graph.txt");
    //testGraph.initialize("Graph.txt");
    testGraph.printGraph();
    //testGraph.printMatrix();

    //testGraph.breadthFirst(testGraph.startNode);



    testGraph.graveyard('P');

    //testGraph.dijstra();
    //testGraph.prim();
    //testGraph.kruskal();

    //testGraph.testPath('P');

    return 0;
}
