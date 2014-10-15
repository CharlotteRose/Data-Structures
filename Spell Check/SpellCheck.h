#ifndef SPELL_CHECK
#define SPELL_CHECK
#include <string>
#include "Node.h"


class SpellCheck{
public:
    SpellCheck(std::string);


    void checkWord(std::string);

    //reads in dictionary file and sets up the spell checker
    bool initialize(std::string);

private:
    void insertWord(std::string);
    void loadDictionary(std::string);

    void testInsert();
    void testSearch();

    void compress();
    void compress(Node*);
    void searchDictionary(std::string &wordToSearch, int currentPosition, Node*& currentNode);
    void printSuggestions(Node*, std::string);

    std::string suggestion;


    //consider creating a hash table to verify that words are in fact in the dictionary
    //reason : umbrella is a word, but umbrell is not

    //child list, but contains A-Z and acts as the first letter in a given word
    Node* firstLetters;

    //used for compressing each of the 26 starting letters and subtrees
    Node* currentRoot;
};

#endif // SPELL_CHECK
