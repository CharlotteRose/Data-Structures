#include <string>
#include <iostream>
#include <fstream>

class Assembler{
public:
    Assembler(std::string fileName){
        fStr.open(fileName.c_str());
        if(fStr.is_open()){
            convertFile(fStr);
            fStr.close();
        }else{
            std::cout << "The file was not found." << std::endl;
        }
    }

    bool convertFile(std::fstream& fStr);
    std::string cleanString(std::string);

private:
    std::fstream fStr;
};
