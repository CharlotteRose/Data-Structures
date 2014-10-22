#include "SpellCheck.h"
#include <string>
#include <iostream>



int main(){
    SpellCheck testSpellCheck("dictionary.txt");
    bool checkingWords = true;
    std::string wordToCheck;


    while(checkingWords){
        std::cout << "Please enter a word to check : ";
        std::cin >> wordToCheck;
        testSpellCheck.checkWord(wordToCheck);
    }


    //testSpellCheck.testSearch();

}
