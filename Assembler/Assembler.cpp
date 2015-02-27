#include "Assembler.h"
#include <algorithm>


bool Assembler::convertFile(std::fstream& fStr){
    std::string currentLine;
    while(!fStr.eof()){
        std::getline(fStr, currentLine);
        if(!currentLine.empty()){
            currentLine = cleanString(currentLine);
            std::cout << currentLine << std::endl;
        }
        else{

        }
    }
}

std::string Assembler::cleanString(std::string input){
  input.erase(std::remove(input.begin(),input.end(),' '),input.end());
  //parse comments out as well
  //while loop to find '/' and copy int value for location
  //then for loop backwards erasing until the '/' is erased

  return input;
}
