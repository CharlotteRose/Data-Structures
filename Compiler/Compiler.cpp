#include "Compiler.h"
#include <iostream>

Compiler::Compiler(){
}

void Compiler::compileFile(std::string inputFile){
    std::string strippedFileName;
    std::string strippedFile;
    std::string tokenFile;
    std::string xmlFile;
    tokenList = new std::list<Token*>();

    //strip the input file of comments and whitespace
    strippedFileName = stripFile(inputFile);
    tokenFile = strippedFileName + ".token";
    xmlFile = strippedFile + ".xml";

    //makes a list that contains the tokens
    tokenizer.getTokens(tokenFile, tokenList);

    //passes the token list into the compile engine for parsing
    compileEngine.recieveTokens(tokenList);

    //recursive descent parsing


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
    bool variable = false;

    while (fin.get(c))
    {
        variable = false;
        if(blockComment == true){
            if(c == '/' && lastChar == '*'){
                blockComment = false;
                lineComment = false;
            }
        }else if(lineComment == true){
            if(c == '\n'){
                lineComment = false;
            }
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
                //check here for var syntax
                // if v, a, r, and a space line up
                char tempVar;
                fout << c;
                /*
                if(c == 'v'){
                    fout << c;

                    tempVar = fin.peek();
                    if(tempVar == 'a'){
                        fin.get(c);
                    }



                    if(c == 'a'){
                        fout << c;
                        tempVar = fin.peek();
                        if(tempVar == 'r'){
                            fin.get(c);
                        }

                        if(tempVar == 'r'){
                            fout << c;

                            tempVar = fin.peek();
                            if(tempVar == ' '){
                                //if whitespace, then we have a variable declaration
                                std::string tempStr;
                                fin >> tempStr;
                                fout << tempStr << ' ';
                                fin >> tempStr;
                                fout << tempStr;

                            }
                        }


                    }
                  //then read the next item into a string, and append a # to it
                }else{
                  fout << c;
                }
                */


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
