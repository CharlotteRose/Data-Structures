#include "Graph.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>

Graph::Graph(){
    startNode = NULL;
    numOfNodes = 0;
    masterList.resize(0);
}

void Graph::initialize(std::string fileToOpen){
    std::ifstream fin(fileToOpen.c_str());
    std::string stringToParse;
    char currentNodeValue;
    char adjacentNodeValue;
    Node* tempNode = NULL;
    Node* placeHolder = NULL;

    if(fin.is_open()){
        fin >> numOfNodes;

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
                        int j = 0;
                        for(it = masterList.begin(); it < masterList.end(); it++, j++){
                        //if the adjacentNodeValue is, grab the Node* from the list
                            if(adjacentNodeValue == masterList[j]->letter){
                                nodeInMaster = true; //we found the node in the master list

                                //add the node to the current node's adjacent list
                                tempNode->addAdjacent(masterList[j]);
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
