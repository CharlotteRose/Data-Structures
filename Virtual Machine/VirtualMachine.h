#include <string>
#include <fstream>
#include <ostream>
#include <iostream>
#include <stack>

enum COMMAND_TYPE{
    MEM_COMMAND,
    ARITH_COMMAND,
    LABEL_COMMAND,
    FUNC_COMMAND,
    INVALID_COMMAND
};

class VirtualMachine{
public:
    VirtualMachine(std::string fileName){
        std::string vmFile = fileName + ".vm";
        std::string asmFile = fileName + ".asm";
        functionMode = false;
        fStr.open(vmFile.c_str());
        std::cout << vmFile << std::endl;
        oStr.open(asmFile.c_str());
        numericValue = 0;
        callNumber = 0;

        if(fStr.is_open()){
            labelNumber = 0;
            convertFile(fStr);
            fStr.close();
            oStr.close();
        }else{
            std::cout << "The file was not found." << std::endl;
        }
    }

private:
    int labelNumber;
    std::fstream fStr;
    std::ofstream oStr;
    std::string cleanString(std::string& currentLine);
    bool convertFile(std::fstream& fStr);
    COMMAND_TYPE checkCommand(std::string currentCommand);
    void outputMemoryCommand();
    void outputArithmetic();
    void outputLabelCommand();
    void outputFunctionCommand();

    void parseLine(std::string currentLine);
    std::string NumberToString(int Number);
    void resetStrings();

    std::string command; //grabs the first
    std::string location; //location array
    std::string labelName; //label name for label commands
    std::string index; //index for location array
    std::string functionName;
    std::string numberIn;

    std::stack<std::string> callStack;
    std::string currentFunction;

    int numericValue;
    int callNumber;
    bool functionMode;
};
