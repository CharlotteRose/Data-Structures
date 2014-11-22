#include "Graph.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include <queue>
#include "PriorityQueue.h"

Graph::Graph(std::string fileToOpen){
    startNode = NULL;
    infStartNode = NULL;

    numOfNodes = 0;
    masterList.resize(0);
    initialize(fileToOpen);
}

void Graph::initialize(std::string fileToOpen){
    std::ifstream fin(fileToOpen.c_str());
    std::string stringToParse;
    char currentNodeValue;
    char adjacentNodeValue;
    Node* tempNode = NULL;
    Node* placeHolder = NULL;
    int adjacencyX = 0;
    int adjacencyY = 0;

    if(fin.is_open()){
        fin >> numOfNodes;
        adjacencyMatrix.resize(numOfNodes);
        for(int i = 0; i < numOfNodes; i++){
            adjacencyMatrix[i].resize(numOfNodes, 0);
        }

        while(!fin.eof()){
            tempNode = NULL; //resets temp node for checks
            placeHolder = NULL; //resets pointer for linking adjacent nodes
            getline(fin, stringToParse);
            if(!stringToParse.empty()){
                currentNodeValue = stringToParse[0];
                //check if currentNodeValue is in the Master List, and if not, add it.

                int i = 0;
                for(it = masterList.begin(); it < masterList.end(); it++, i++){
                    //if the currentNodeValue is, grab the Node* from the list
                    if(currentNodeValue == masterList[i]->letter){
                        tempNode = masterList[i];
                        break;
                    }
                }



                if(tempNode == NULL){
                    //the currentNodeValue was not in the master list, so we add it
                    tempNode = new Node(currentNodeValue);
                    tempNode->nodeNumber = masterList.size();
                    adjacencyX = tempNode->nodeNumber;
                    masterList.push_back(tempNode);
                }


                //if the starting node is null, assign the first node added to the Master List
                if(startNode == NULL){
                    startNode = tempNode;
                }




                //starts at one because we already grab the first value from this line in the file
                for(int i = 1; i < strlen(stringToParse.c_str()); i++){
                    bool nodeInMaster = false;
                    adjacentNodeValue = stringToParse[i];

                    //if the node does not contain a letter, we discard it

                    if(isalpha(adjacentNodeValue)){
                        //first check if it's in the master list already, and if so, grab it

                        bool negNumber = false;
                        int weight = 0;
                        int weightBuffer;
                        i++; //moves to the next value in the string to parse weights
                        if(stringToParse[i] == '-'){
                            negNumber = true;
                            i++; //if negative sign, moves to next value to parse weight
                        }

                        do{
                            weightBuffer = stringToParse[i] - '0'; //grabs the current char value and converts to int
                            weight = (weight * 10) + weightBuffer; //reads the int value char by char
                        }while(isdigit(stringToParse[i+1]));

                        if(negNumber){
                            weight *= -1;
                        }

                        //weight = stringToParse[i+1] - '0'; //weights always follow node values



                        int j = 0;
                        for(it = masterList.begin(); it < masterList.end(); it++, j++){
                        //if the adjacentNodeValue is, grab the Node* from the list
                            if(adjacentNodeValue == masterList[j]->letter){
                                nodeInMaster = true; //we found the node in the master list

                                //add the node to the current node's adjacent list
                                tempNode->addAdjacent(masterList[j]);
                                tempNode->weight.push_back(weight);

                                adjacencyY = tempNode->nodeNumber;

                                adjacencyMatrix[adjacencyY][adjacencyX] += 1;
                                break;
                            }
                        }//for
                        if(nodeInMaster == false){
                            //adjacent node was not found in master, so make new node and add to master
                            placeHolder = new Node(adjacentNodeValue);

                            placeHolder->nodeNumber = masterList.size();
                            masterList.push_back(placeHolder);

                            //then add to the current node's adjacent list
                            tempNode->addAdjacent(placeHolder);
                            tempNode->weight.push_back(weight);
                            placeHolder = NULL;
                        }
                    }

                } //for

            }
        }//while

    } else{
        std::cout << fileToOpen << " was not found or does not exist." << std::endl << std::endl;
    }
}


void Graph::printGraph(){
    int i = 0;
    Node* tempNode = NULL;
    for(it = masterList.begin(); it < masterList.end(); it++, i++){
        tempNode = masterList[i];
        tempNode->printNode();
    }
}


void Graph::depthFirst(Node* currentNode){
    currentNode->isVisited = true;

    std::cout << "Current Node is " << currentNode->letter << std::endl;
    int i = 0;

    for(currentNode->it = currentNode->adjacentList.begin();
        currentNode->it < currentNode->adjacentList.end(); currentNode->it++, i++){

        if(currentNode->adjacentList[i]->isVisited == false){
            //if the node hasn't been visited, recurse
            depthFirst(currentNode->adjacentList[i]);
        }
    }

}


void Graph::breadthFirst(Node* startNode){
    std::queue <Node*> nodeQueue;
    Node* x;
    Node* y;

    startNode->isVisited = true;
    nodeQueue.push(startNode);

    while(!nodeQueue.empty()){
        x = nodeQueue.front();
        nodeQueue.pop(); // grabs next node to check adjacencyList
        std::cout << "Current node is " << x->letter << std::endl;
        int i = 0;
        for(x->it = x->adjacentList.begin(); x->it < x->adjacentList.end(); x->it++, i++){
            if(x->adjacentList[i]->isVisited == false){
                x->adjacentList[i]->isVisited = true;
                nodeQueue.push(x->adjacentList[i]);
            }
        }
    }


}


void Graph::printMatrix(){

    for(int i = 0; i < numOfNodes; i++){
        for(int j = 0; j < numOfNodes; j++){

            std::cout << adjacencyMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


void Graph::testQueue(){
    PriorityQueue testQueue;
    Node* tempNode = NULL;

    testQueue.push(masterList[5], 5, NULL);
    testQueue.push(masterList[2], 6, NULL);
    testQueue.push(masterList[1], 5, NULL);
    testQueue.push(masterList[3], 6, NULL);
    testQueue.push(masterList[0], 7, NULL);


    while(!testQueue.isEmpty()){
        tempNode = testQueue.front();
        std::cout << tempNode->letter << " ";
        testQueue.pop();
    }


}


void Graph::dijkstra(Node* currentNode, int pathSum){
    if(currentNode == startNode){
        currentNode->isVisited = true;
    }
    int i = 0;


    //add to the queue all adjacent nodes that haven't been visited already
    for(currentNode->it = currentNode->adjacentList.begin();
        currentNode->it < currentNode->adjacentList.end();
        currentNode->it++, i++){
        if(currentNode->adjacentList[i]->isVisited == false){
            //adds to queue for checking algorithm

            priorityQueue.push(currentNode->adjacentList[i], pathSum + currentNode->weight[i], currentNode);
        }
    }

    //pop the lowest value on the queue, and if it hasn't been visited already, mark it as visited
    Node* tempNode = NULL;

    while(!priorityQueue.isEmpty()){
        tempNode = priorityQueue.front();

        int newPathSum = priorityQueue.frontPriority();
        //priorityQueue.pop();

        if(tempNode == NULL)
        {
            break;
        }



        if(!tempNode->isVisited){
            tempNode->isVisited = true;
            tempNode->priorNode = priorityQueue.frontPriorNode();

            tempNode->pathSum = newPathSum;
            dijkstra(tempNode, tempNode->pathSum);
        }

        priorityQueue.pop();

    }


}

void Graph::graveyard(Node* currentNode, int pathSum, bool& infTime){
    if(currentNode == startNode){
        currentNode->isVisited = true;
    }
    int i = 0;

    if(currentNode->weight.size() == 1){
        //this scenario means the current node is a portal

        if(currentNode->adjacentList[0]->isVisited == true){
            //this scenario covers updating a path, in case of negative values, if the path had been checked prior
            if(pathSum + currentNode->weight[0] < currentNode->adjacentList[0]->pathSum){
                currentNode->adjacentList[0]->pathSum = pathSum + currentNode->weight[0];
                currentNode->adjacentList[0]->priorNode = currentNode;
                graveyard(currentNode->adjacentList[0], currentNode->adjacentList[0]->pathSum, infTime);
            }else{
                std::cout << "THIS SHOULD NOT BE PRINTING SO CHECK ME" << std::endl;
            }


        }else{
            //this scenario means the target space has not been tested, and should be handled as normal
            priorityQueue.push(currentNode->adjacentList[0], pathSum + currentNode->weight[0], currentNode);
        }

        //check for infinite time

        infTime = infCheck(currentNode->adjacentList[0], currentNode->letter);

        //reset infinite time checks for next portals
        resetInfChecks();

    }else{
        //this scenario means the current node is not a portal

        //add to the queue all adjacent nodes that haven't been visited already
        for(currentNode->it = currentNode->adjacentList.begin();
            currentNode->it < currentNode->adjacentList.end();
            currentNode->it++, i++){
            if(currentNode->adjacentList[i]->isVisited == false){
                //adds to queue for checking algorithm

                priorityQueue.push(currentNode->adjacentList[i], pathSum + currentNode->weight[i], currentNode);
            }
        }



        }

        //pop the lowest value on the queue, and if it hasn't been visited already, mark it as visited
        Node* tempNode = NULL;

        while(!priorityQueue.isEmpty()){
            tempNode = priorityQueue.front();

            int newPathSum = priorityQueue.frontPriority();
            //priorityQueue.pop();

            if(tempNode == NULL)
            {
                break;
            }



            if(!tempNode->isVisited){
                tempNode->isVisited = true;
                tempNode->priorNode = priorityQueue.frontPriorNode();

                tempNode->pathSum = newPathSum;
                graveyard(tempNode, tempNode->pathSum, infTime);
            }

            priorityQueue.pop();

    }


}

void Graph::infCheck(Node* currentNode, int infPathSum){
    if(currentNode == infStartNode){
        currentNode->infTimeCheck = true;
    }
    int i = 0;


    //add to the queue all adjacent nodes that haven't been visited already
    for(currentNode->it = currentNode->adjacentList.begin();
        currentNode->it < currentNode->adjacentList.end();
        currentNode->it++, i++){
        if(currentNode->adjacentList[i]->infTimeCheck == false){
            //adds to queue for checking algorithm

            infPriorityQueue.push(currentNode->adjacentList[i], infPathSum + currentNode->weight[i], currentNode);
        }
    }

    //pop the lowest value on the queue, and if it hasn't been visited already, mark it as visited
    Node* tempNode = NULL;

    while(!infPriorityQueue.isEmpty()){
        tempNode = infPriorityQueue.front();

        int newinfPathSum = infPriorityQueue.frontPriority();

        if(tempNode == NULL)
        {
            break;
        }



        if(!tempNode->infTimeCheck){
            tempNode->infTimeCheck = true;
            tempNode->infPriorNode = infPriorityQueue.frontPriorNode();

            tempNode->infPathSum = newinfPathSum;
            infCheck(tempNode, tempNode->infPathSum);
        }

        infPriorityQueue.pop();

    }


}





bool Graph::infCheck(Node* newStartNode, char targetNodeLetter){
    resetInfChecks();
    infStartNode = newStartNode;



    //fix inf check
    infCheck(infStartNode, 0);

    //fix testInfPath
    timeValue = testInfPath(targetNodeLetter);



    if(timeValue < 0){
        return true;
    }


    return false;

}


void Graph::graveyard(char targetNodeLetter){
    Node* exitNode = NULL;
    bool infTime = false;
    resetChecks();
    int i = 0;
    for(it = masterList.begin(); it < masterList.end(); it++, i++){
        if(masterList[i]->letter == targetNodeLetter){
            exitNode = masterList[i];
        }
    }

    if(exitNode != NULL){
        graveyard(startNode, 0, infTime);


        if(exitNode->isVisited == false){
            std::cout << "An exit is impossible to find" << std::endl;
        }else if(infTime){
            std::cout << "An infinite time loop is possible" << std::endl;
        }else{
            testPath(targetNodeLetter);
        }

    }else{
        std::cout << "There was no exit node found" << std::endl;
    }

}



void Graph::prim(Node* currentNode, int edgeWeight){
    if(currentNode == startNode){
        currentNode->isVisited = true;
    }
    int i = 0;


    //add to the queue all adjacent nodes that haven't been visited already
    for(currentNode->it = currentNode->adjacentList.begin();
        currentNode->it < currentNode->adjacentList.end();
        currentNode->it++, i++){
        if(currentNode->adjacentList[i]->isVisited == false){
            //adds nodes by edge weight to queue for checking algorithm

            priorityQueue.push(currentNode->adjacentList[i], currentNode->weight[i], currentNode);
        }
    }

    //pop the lowest value on the queue, and if it hasn't been visited already, mark it as visited
    Node* tempNode = NULL;

    while(!priorityQueue.isEmpty()){
        tempNode = priorityQueue.front();
        int edgeWeight = priorityQueue.frontPriority();
        //priorityQueue.pop();

        if(tempNode == NULL)
        {
            break;
        }


        //prior node list not linking fully for some reason


        if(!tempNode->isVisited){
            tempNode->isVisited = true;
            tempNode->priorNode = priorityQueue.frontPriorNode();

            //tempNode->pathSum = edgeWeight;
            prim(tempNode, edgeWeight);
        }

        priorityQueue.pop();

    }


}


void Graph::prim(){
    Node* tempNode = NULL;
    resetChecks();

    prim(startNode, 0);

}




void Graph::kruskal(){
    resetChecks();


    //add all edges into the priority queue

    int j = 0;
    for(it = masterList.begin();
        it < masterList.end();
        it++, j++){

        int i = 0;
        for(masterList[j]->it = masterList[j]->adjacentList.begin();
            masterList[j]->it < masterList[j]->adjacentList.end();
            masterList[j]->it++, i++){
            if(masterList[j]->adjacentList[i]->isVisited == false){
                //adds nodes by edge weight to queue for checking algorithm

                priorityQueue.push(masterList[j]->adjacentList[i], masterList[j]->weight[i], masterList[j]);
            }
        }
    }

    //pop the lowest value on the queue, and if it hasn't been visited already, mark it as visited
    Node* tempNode = NULL;

    priorityQueue.printQueue();

    while(!priorityQueue.isEmpty()){
        bool duplicate = false;
        tempNode = priorityQueue.front();
        int edgeWeight = priorityQueue.frontPriority();
        //priorityQueue.pop();

        if(tempNode == NULL)
        {
            break;
        }

        if(!tempNode->isVisited && priorityQueue.frontPriorNode()->isVisited == false){


                tempNode->isVisited = true;
                tempNode->priorNode = priorityQueue.frontPriorNode();

        }

        priorityQueue.pop();

    }


}





void Graph::resetChecks(){

    int i = 0;
    for(this->it = masterList.begin(); this->it < masterList.end();
        this->it++, i++){

        masterList[i]->isVisited = false;
        masterList[i]->infTimeCheck = false;
        masterList[i]->pathSum = 0;
        masterList[i]->infPathSum = 0;
    }
}

void Graph::resetInfChecks(){

    int i = 0;
    for(this->it = masterList.begin(); this->it < masterList.end();
        this->it++, i++){

        masterList[i]->infTimeCheck = false;
        masterList[i]->infPathSum = 0;
    }
}


void Graph::testPath(char pathValue){
    Node* tempNode = NULL;
    int i = 0;

    for(it = masterList.begin();
        it < masterList.end();
        it++, i++){

        if(pathValue == masterList[i]->letter){
            tempNode = masterList[i];
        }
    }

    if(tempNode != NULL){
        int totalPath = tempNode->pathSum;
        while(tempNode != NULL){
            std::cout << tempNode->letter << " ";
            tempNode = tempNode->priorNode;
        }
        std::cout << std::endl << "Total path was " << totalPath << std::endl;
    }else{
        std::cout << "Node value not found" << std::endl;
    }
}

int Graph::testInfPath(char pathValue){
    Node* tempNode = NULL;
    int i = 0;

    for(it = masterList.begin();
        it < masterList.end();
        it++, i++){

        if(pathValue == masterList[i]->letter){
            tempNode = masterList[i];
        }
    }

    if(tempNode != NULL){
        //starts with the weighted value of the target node
        int totalPath = tempNode->weight[0];
        while(tempNode != NULL){

            if(tempNode->infPriorNode == NULL){
                totalPath += tempNode->pathSum;
            }else{
                totalPath = totalPath + (tempNode->infPathSum - tempNode->infPriorNode->infPathSum);
            }
            tempNode = tempNode->infPriorNode;
        }
        return totalPath;
    }else{
        std::cout << "Node value not found" << std::endl;
    }
}


