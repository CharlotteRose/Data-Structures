#include "Compiler.h"
#include <iostream>

Compiler::Compiler(){
}

void Compiler::compileFile(std::string inputFile){
    std::string strippedFileName;
    std::string strippedFile;

    //strip the input file of comments and whitespace
    strippedFileName = stripFile(inputFile);


    //pass the strippedFile to the syntax analyzer and output the tokens to XML

}

std::string Compiler::stripFile(std::string inputFile){
    int dotLoc = 0;
    for(dotLoc = 0; dotLoc < inputFile.length(); dotLoc++){
        if(inputFile[dotLoc] == '.')
          break;
    }

    std::string strippedFile = inputFile.substr(0, dotLoc);
    std::string tokenFile = strippedFile + ".token";
    std::ifstream fin(inputFile.c_str());
    std::ofstream fout(tokenFile.c_str());

    if(fin.is_open()){
    char c;
    char lastChar = ' ';
    bool lineComment = false;
    bool blockComment = false;

    while (fin.get(c))
    {
        if(blockComment == true){
            if(c == '/' && lastChar == '*'){
                blockComment = false;
                lineComment = false;
            }
        }else if(lineComment == true){
            if(c == '\n'){
                lineComment = false;
            }
        }else if(c == ' '){
        }else if(c == '\n'){
            if(c == '\n'){
                lineComment = false;
            }
        }else if(c == '\t'){

        }else{
            if(c == '/'){
                char temp = fin.peek();
                if(temp == '/'){
                    lineComment = true;
                }else if(temp == '*'){
                    blockComment = true;
                }else{
                  //output
                  fout << c;
                }
            }else{
              fout << c;
            }
        }

        lastChar = c;
    }
        fin.close();
        fout.close();
    }else{
       std::cout << "the file could not be found" << std::endl;
    }


    return strippedFile;
}
