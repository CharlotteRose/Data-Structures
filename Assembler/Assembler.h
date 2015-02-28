#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <list>

struct Label{
    std::string labelName;
    int address;
};

class Assembler{
public:
    Assembler(std::string fileName){
        std::string asmFile = fileName + ".asm";
        std::string hackFile = fileName + ".hack";
        fStr.open(asmFile.c_str());
        oStr.open(hackFile.c_str());
        nextFreeAddress = 16;
        isAinstruct = false;
        if(fStr.is_open()){
            loadLabels(asmFile);
            loadLabels2(asmFile);
            printLabelTable();
            convertFile(fStr);
            fStr.close();
            oStr.close();
        }else{
            std::cout << "The file was not found." << std::endl;
        }
    }

    bool convertFile(std::fstream& fStr);
    bool loadLabels(std::string fileName);
    bool loadLabels2(std::string fileName);
    std::string cleanString(std::string&);
    bool checkLabel(Label*);

    void printLabelTable();
    void parseLine(std::string);
    std::string convertToBinaryString(int);
    std::string getLabelAddress(std::string);
    void resetStrings();
    void buildBinaryOutput();

private:
    std::fstream fStr;
    std::ofstream oStr;
    std::list<Label*> labelTable;
    int nextFreeAddress;
    std::string dest;
    std::string jump;
    std::string comp;
    std::string binaryOut;
    bool isAinstruct;
};
