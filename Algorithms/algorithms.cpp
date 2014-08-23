#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;

void checkParentheses(string);
void parseFile(std::fstream&);
void printResult(bool);

int main(){
    string fileName = "";
    cout << "Enter file name to parse parentheses: ";
    cin >> fileName;
    checkParentheses(fileName);
    return 0;
}


void checkParentheses(string fileName){
    std::fstream readFile;

    readFile.open(fileName.c_str());
    if(readFile.is_open()){ //tests that file exists
            parseFile(readFile);
        readFile.close();
    }
    else
        cout << "The file could not be opened or does not exist. Exiting.";
}


void parseFile(std::fstream& readFile)
{
    int leftParenthesisCount = 0;
    bool allPairsMatch = true; //used to separate message code into separate function
    char checkChar;

    /* Counts the number of ( then subtracts this value when a matching ) is found
    if the count becomes negative, there is an incomplete pair and aborts immediately
    if the count holds a non-zero value after the entire file is parsed, aborts.
    otherwise, the file has no pairs or all pairs match.
    */


    while(readFile.eof() == false && allPairsMatch == true)
    {
        readFile >> checkChar;
        if (checkChar == '(')
                leftParenthesisCount++;
        else if (checkChar == ')')
                leftParenthesisCount--;


        if (leftParenthesisCount < 0)
        {
            allPairsMatch = false;
        }

    }
    //this goes in a loop

    if (leftParenthesisCount == 0){
        allPairsMatch = true;
        printResult(allPairsMatch);
    }
    else
    {
        allPairsMatch = false;
        printResult(allPairsMatch);
    }
}

void printResult(bool allPairsMatch)
{
    if (allPairsMatch == true){
        cout << "There were no mismatched pairs of parenthesis." << endl;
    }
    else
        cout << "There was one or more mismatched pairs of parenthesis." << endl;
}
