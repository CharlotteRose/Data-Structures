#include "Assembler.h"
#include <iostream>
#include <string>

int main(){
    std::string fileName;
    std::cout << "Enter the filename to convert from .asm to .hack" << std::endl;
    std::cin >> fileName;
    Assembler assembler(fileName);
}
