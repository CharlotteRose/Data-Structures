#include "SpellCheck.h"
#include "Node.h"
#include <string>
#include <iostream>


SpellCheck::SpellCheck(){
    initialize("TEST");
    compress();
}


void SpellCheck::checkWord(std::string wordToCheck){
    Node* travel = firstLetters;
    Node* tempNode = NULL;
}

bool SpellCheck::initialize(std::string wordFile){
    firstLetters = new Node('A');
    Node* travel = firstLetters;
    Node* tempNode = NULL;

    //English Alphabet starting at B
    for(int i = 1; i < 26; i++){
        tempNode = new Node('A' + i);
        travel->nextChild = tempNode;
        travel = travel->nextChild;
        tempNode = NULL;
    }
}

void SpellCheck::insertWord(std::string newWord){
    Node* travel = firstLetters;
    Node* tempNode = NULL;
    bool letterFound = false;

    //American English Alphabet
    for(int i = 0; i < 26; i++){
        if(travel != NULL){
            if(toupper(newWord[0]) == travel->value[0]){
                letterFound = true;
                break;
            }
            travel = travel->nextChild;
        }
    }



    if(letterFound == true){
        std::cout << "First letter is " << travel->value << std::endl;
        //starts at 1 because first letter is already checked
        for(int i = 1; i < newWord.length(); i++){
            std::string charToMatch(1, newWord[i]);
            tempNode = travel->matchChild(charToMatch);

            if(tempNode != NULL){
                //if a child node matches the next char in the string, advance travel node
                travel = tempNode;
                std::cout << "exist" << std::endl;
            }else{
                //if char not found in child list, create a new child with the value, then advance
                if(!isalpha(newWord[i])){
                    //if a non letter character is detected, stops adding to dictionary
                    break;
                }

                tempNode = new Node(newWord[i]);
                travel->addChild(tempNode);
                travel = tempNode;
                std::cout << "new" << std::endl;
            }
        }

    }else{
        std::cout << "ERROR - Word doesn't start with a letter" << std::endl;
    }

}

//compresses all of the primary letter trees
void SpellCheck::compress(){

    currentRoot = firstLetters;
    //performs a compress on each of the starting letters, treating them as their own root
    while(currentRoot != NULL){
        std::cout << "Checking trie tree " << currentRoot->value << std::endl;
        compress(currentRoot);
        currentRoot = currentRoot->nextChild;
    }
}

void SpellCheck::compress(Node* currentNode){
    Node* travel = currentNode;
    Node* tempNode = NULL;
    bool compressionMade = false;

    if(travel != NULL){
        if(travel != currentRoot){
            if(travel->numChildren == 1){
                //if node has exactly one child, combines the child value into the parent value
                travel->value = travel->value + travel->childListHead->value;
                travel->numChildren = travel->childListHead->numChildren;

                //readies the single child for deletion
                tempNode = travel->childListHead;

                //copies the tail information for the child's own child list
                travel->childListTail = travel->childListHead->childListTail;

                //child list's list becomes the new child list of the current node
                travel->childListHead = travel->childListHead->childListHead;

                //deletes the child node and cleans up pointer
                delete tempNode;
                tempNode = NULL;

                compressionMade = true;
                std::cout << "Compressing to  " << travel->value << std::endl;
                compress(travel);



            }
        }

        if(travel != NULL){
            travel = travel->childListHead;
        }

        while(travel != NULL){
            compress(travel);
            travel = travel->nextChild;
        }

    }
}

void SpellCheck::testInsert(){
    std::string firstWord = "BLACK";
    std::string secondWord = "BLAST";
    std::string thirdWord = "BLASTER";
    std::string fourthWord = "BIRTH";
    insertWord(firstWord);
    insertWord(secondWord);
    insertWord(thirdWord);
    insertWord(fourthWord);

    compress();

}
