#include "SpellCheck.h"
#include "Node.h"
#include <string>
#include <iostream>
#include <fstream>


SpellCheck::SpellCheck(std::string dictionaryFile){
    std::cout << "Loading dictionary file..." << std::endl;
    std::cout << "Please be patient, this may take awhile..." << std::endl;
    initialize(dictionaryFile);
    std::cout << "Compressing words..." << std::endl;
    std::cout << "Please be patient, this may take awhile..." << std::endl;
    compress();

    std::cout << "Ready for searching..." << std::endl;
    suggestion = "";
}


void SpellCheck::checkWord(std::string wordToCheck){
    Node* travel = firstLetters;
    suggestion = "";

    //Node* tempNode = NULL;
    bool letterFound = false;

    //American English Alphabet
    for(int i = 0; i < 26; i++){
        if(travel != NULL){
            if(toupper(wordToCheck[0]) == travel->value[0]){
                letterFound = true;
                break;
            }
            travel = travel->nextChild;
        }
    }

    if(letterFound == true){
        //starts checking against the first node in the matching letter tree
        searchDictionary(wordToCheck, 0, travel);
    }else{
        std::cout << "Word does not start with a letter." << std::endl;
    }

}

void SpellCheck::searchDictionary(std::string &wordToSearch, int currentPosition, Node* &currentNode){
    Node* travel = currentNode;
    Node* placeHolder = NULL;
    bool validLetter = false;

    //checks all characters in the current node, unless word to search has been found

    for(int i = 0; i < travel->value.length(); i++){
        if(toupper(wordToSearch[currentPosition]) == travel->value[i]){
            //if the values match, converts the char into a string and adds to the suggestion prefix
            std::string tempChar(1, travel->value[i]);
            suggestion = suggestion + tempChar;
            currentPosition++;
            validLetter = true;
            //check that the current position doesn't extend past the string length
            if(currentPosition > wordToSearch.length()){
                break;
            }

        }else{
            //invalid letter
            validLetter = false;
            //if the current letters do not match, suggestion needs to complete the remainder of the string
            for(int j = i; j < travel->value.length(); j++){
                std::string tempChar(1, travel->value[i]);
                suggestion = suggestion + tempChar;
            }

            break;
        }
    }

    if(currentPosition >= wordToSearch.length()){
        //word is found

        std::cout << wordToSearch << " was in the dictionary." << std::endl;
        return;
    }
    if(validLetter == true && currentPosition <= wordToSearch.length()){
            //converts the next character in the word to search
            std::string tempChar(1, toupper(wordToSearch[currentPosition]));
            //checks if travel contains a child that starts with the next character in wordToSearch
            placeHolder = travel;
            travel = travel->matchChild(tempChar);


            if(travel != NULL){
                //there is a next letter, so recurse
                searchDictionary(wordToSearch, currentPosition, travel);
            }else{
                //there is no next letter that matches, print suggestions
                std::cout << "SUGGESTING1" << std::endl;
                printSuggestions(placeHolder, wordToSearch);
            }
    }else if(validLetter == false){
        //letters didn't match so print suggestions
        std::cout << "SUGGESTING2" << std::endl;
        printSuggestions(travel, wordToSearch);
    }



}

void SpellCheck::printSuggestions(Node* currentNode, std::string wordToFind){

    Node* travel;

    if(currentNode != NULL){
        travel = currentNode->childListHead;
    }else{
        travel = currentNode;
    }





    std::cout << wordToFind << " was not found." << std::endl;
    std::cin.get();

    if(travel != NULL){
        std::cout << "Did you mean..." << std::endl;
        std::cin.get();
        while(travel != NULL){
            std::cout << suggestion + travel->value << std::endl;
            travel = travel->nextChild;
        }

    }else{
        std::cout << "No suggestions were found" << std::endl;
    }
}

bool SpellCheck::initialize(std::string dictionaryFile){
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

    loadDictionary(dictionaryFile);
}



void SpellCheck::loadDictionary(std::string dictionaryFile){
    std::ifstream fin;
    std::string wordToInsert;
    fin.open(dictionaryFile.c_str());

    if(fin.is_open()){

        while(!fin.eof()){
            fin >> wordToInsert;
            insertWord(wordToInsert);
        }

    }else{
        std::cout << "FILE DID NOT LOAD" << std::endl;
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
        //starts at 1 because first letter is already checked
        for(int i = 1; i < newWord.length(); i++){
            std::string charToMatch(1, toupper(newWord[i]));
            tempNode = travel->matchChild(charToMatch);

            if(tempNode != NULL){
                //if a child node matches the next char in the string, advance travel node
                travel = tempNode;
            }else{
                //if char not found in child list, create a new child with the value, then advance
                if(!isalpha(newWord[i])){
                    //if a non letter character is detected, stops adding to dictionary
                    break;
                }

                tempNode = new Node(newWord[i]);
                travel->addChild(tempNode);
                travel = tempNode;
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


void SpellCheck::testSearch(){

    std::string firstWord = "BOOKS";
    std::string secondWord = "boots";
    std::string thirdWord = "boot";
    std::string fourthWord = "BOOLEAN";
    insertWord(firstWord);
    insertWord(secondWord);
    insertWord(thirdWord);
    insertWord(fourthWord);
    compress();

    checkWord("BOOKS");
    checkWord("BOOT");
    checkWord("BOLT");
}
