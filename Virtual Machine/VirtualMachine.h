#include <string>
#include <fstream>
#include <ostream>
#include <iostream>

class VirtualMachine{
public:
    VirtualMachine(std::string fileName){
        std::string vmFile = fileName + ".vm";
        std::string asmFile = fileName + ".asm";
        fStr.open(vmFile.c_str());
        std::cout << vmFile << std::endl;
        oStr.open(asmFile.c_str());
        if(fStr.is_open()){
            convertFile(fStr);
            fStr.close();
            oStr.close();
        }else{
            std::cout << "The file was not found." << std::endl;
        }
    }

private:
    std::fstream fStr;
    std::ofstream oStr;
    std::string cleanString(std::string& currentLine);
    bool convertFile(std::fstream& fStr);
    bool checkCommand(std::string currentCommand);
    void outputMemoryCommand();
    void outputArithmetic();
    void parseLine(std::string currentLine);
    void resetStrings();

    std::string command; //grabs the first
    std::string location; //location array
    std::string index; //index for location array
};
