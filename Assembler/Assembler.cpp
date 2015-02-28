#include "Assembler.h"
#include <algorithm>


bool Assembler::convertFile(std::fstream& fStr){
    std::string currentLine;
    while(!fStr.eof()){
        std::getline(fStr, currentLine);
        currentLine = cleanString(currentLine);
        if(!currentLine.empty()){
            //stripped file to parse easier
            //first reset fields
            if(currentLine[0] != '('){
                parseLine(currentLine);
            }
        }
        else{

        }
    }
}

bool Assembler::loadLabels(std::string fileName){
    std::fstream fStr;
    fStr.open(fileName.c_str());
    std::string currentLine;

    //declare preset labels in label table
    std::cout << "Adding preset labels to the table now." << std::endl;

    Label* tempLabel = new Label();
    tempLabel->labelName = "SP";
    tempLabel->address = 0;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "LCL";
    tempLabel->address = 1;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "ARG";
    tempLabel->address = 2;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "THIS";
    tempLabel->address = 3;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "THAT";
    tempLabel->address = 4;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "R0";
    tempLabel->address = 0;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "R1";
    tempLabel->address = 1;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "R2";
    tempLabel->address = 2;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "R3";
    tempLabel->address = 3;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "R4";
    tempLabel->address = 4;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "R5";
    tempLabel->address = 5;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "R6";
    tempLabel->address = 6;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "R7";
    tempLabel->address = 7;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "R8";
    tempLabel->address = 8;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "R9";
    tempLabel->address = 9;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "R10";
    tempLabel->address = 10;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "R11";
    tempLabel->address = 11;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "R12";
    tempLabel->address = 12;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "R13";
    tempLabel->address = 13;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "R14";
    tempLabel->address = 14;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "R15";
    tempLabel->address = 15;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "SCREEN";
    tempLabel->address = 16384;
    labelTable.push_back(tempLabel);

    tempLabel = new Label();
    tempLabel->labelName = "KBD";
    tempLabel->address = 24576;
    labelTable.push_back(tempLabel);

    std::cout << "Adding declared labels to the table now." << std::endl;

    bool newLabel = false;
    while(!fStr.eof()){
        std::getline(fStr, currentLine);
        currentLine = cleanString(currentLine);
        if(!currentLine.empty()){
            //stripped file, populate declared labels in label table

            //if label found
            if(currentLine[0] == '(' && currentLine[currentLine.length() - 1] == ')'){
                currentLine.erase(currentLine.end() -1);
                currentLine.erase(currentLine.begin());

                tempLabel = new Label();
                tempLabel->labelName = currentLine;
                tempLabel->address = 0; //initialized in the check
                newLabel = checkLabel(tempLabel);

                if(newLabel == false){
                    delete tempLabel; //frees memory if the label already exists
                }
            }
        }
    }
    fStr.close();
}

void Assembler::parseLine(std::string currentLine){
    resetStrings();
    std::string tempString = "";
    int intAddressValue;

    if(currentLine[0] == '@'){
        isAinstruct = true;

        //because it's an A instruction, we can remove the @ now
        currentLine.erase(currentLine.begin());
        //and we can start to build our string, 0 for an A Instruction
        binaryOut += '0';
    }else{
        isAinstruct = false;

        //start to build string, 111 for C Instruction
        binaryOut += "111";
    }

    if(isAinstruct){
        //A instructions

        if(isalpha(currentLine[0])){
            //Label
            tempString += getLabelAddress(currentLine);
            binaryOut += tempString;
        } else if(isdigit(currentLine[0])){
            //Direct Address
            intAddressValue = atoi(currentLine.c_str());

            tempString = convertToBinaryString(intAddressValue);
            binaryOut += tempString;

            //we now have a line of binary code and output it to the .hack file
        }
        //Otherwise, we just ignore the line because it's improperly formatted

    }else{
        //C instructions
        bool destIsNull = true;
        bool jumpIsNull = true;
        bool setABit = false;

        for(int i = 0; i < currentLine.length(); i++){
            if(currentLine[i] == '='){
                destIsNull = false;
            }
            if(currentLine[i] == ';'){
                jumpIsNull = false;
            }
        }

        int k = 0;
        if(destIsNull == false){
            while(currentLine[k] != '='){
                dest += currentLine[k];
                k++;
            }

            if(currentLine[k] == '='){
                k++;
            }
            for(k; k < currentLine.length(); k++){
                comp += currentLine[k];
                if(currentLine[k] == 'M'){
                    setABit = true;
                }
            }
        }else{
            while(currentLine[k] != ';'){
                comp += currentLine[k];
                if(currentLine[k] == 'M'){
                    setABit = true;
                }
                k++;
            }
            if(currentLine[k] == ';'){
                k++;
            }
            for(k; k < currentLine.length(); k++){
                jump += currentLine[k];
            }

        }

        //build string and output

        if(setABit == true){
            binaryOut += '1';
        }else{
            binaryOut += '0';
        }

        buildBinaryOutput();
    }

    if(!binaryOut.empty()){
        oStr << binaryOut << std::endl;
    }
}

void Assembler::buildBinaryOutput(){
    if(binaryOut[3] == '1'){
        if(comp == "M"){
            binaryOut += "110000";
        }
        if(comp == "!M"){
            binaryOut += "110001";
        }
        if(comp == "-M"){
            binaryOut += "110011";
        }
        if(comp == "M+1"){
            binaryOut += "110111";
        }
        if(comp == "M-1"){
            binaryOut += "110010";
        }
        if(comp == "D+M"){
            binaryOut += "000010";
        }
        if(comp == "D-M"){
            binaryOut += "010011";
        }
        if(comp == "M-D"){
            binaryOut += "000111";
        }
        if(comp == "D&M"){
            binaryOut += "000000";
        }
        if(comp == "D|M"){
            binaryOut += "010101";
        }
    }else{
        if(comp == "0"){
            binaryOut += "101010";
        }
        if(comp == "1"){
            binaryOut += "111111";
        }
        if(comp == "-1"){
            binaryOut += "111010";
        }
        if(comp == "D"){
            binaryOut += "001100";
        }
        if(comp == "A"){
            binaryOut += "110000";
        }
        if(comp == "D!"){
            binaryOut += "001101";
        }
        if(comp == "!A"){
            binaryOut += "110001";
        }
        if(comp == "-D"){
            binaryOut += "001111";
        }
        if(comp == "-A"){
            binaryOut += "110011";
        }
        if(comp == "D+1"){
            binaryOut += "011111";
        }
        if(comp == "A+1"){
            binaryOut += "110111";
        }
        if(comp == "D-1"){
            binaryOut += "001110";
        }
        if(comp == "A-1"){
            binaryOut += "110010";
        }
        if(comp == "D+A"){
            binaryOut += "000010";
        }
        if(comp == "D-A"){
            binaryOut += "010011";
        }
        if(comp == "A-D"){
            binaryOut += "000111";
        }
        if(comp == "D&A"){
            binaryOut += "000000";
        }
        if(comp == "D|A"){
            binaryOut += "010101";
        }

    }



    if(dest == ""){
        binaryOut += "000";
    }
    if(dest == "M"){
        binaryOut += "001";
    }
    if(dest == "D"){
        binaryOut += "010";
    }
    if(dest == "MD"){
        binaryOut += "011";
    }
    if(dest == "A"){
        binaryOut += "100";
    }
    if(dest == "AM"){
        binaryOut += "101";
    }
    if(dest == "AD"){
        binaryOut += "110";
    }
    if(dest == "AMD"){
        binaryOut += "111";
    }

    if(jump == ""){
        binaryOut += "000";
    }
    if(jump == "JGT"){
        binaryOut += "001";
    }
    if(jump == "JEQ"){
        binaryOut += "010";
    }
    if(jump == "JGE"){
        binaryOut += "011";
    }
    if(jump == "JLT"){
        binaryOut += "100";
    }
    if(jump == "JNE"){
        binaryOut += "101";
    }
    if(jump == "JLE"){
        binaryOut += "110";
    }
    if(jump == "JMP"){
        binaryOut += "111";
    }

    //validation, lest it be skipped
    if(binaryOut.length() != 16){
        binaryOut = "";
    }

}

std::string Assembler::getLabelAddress(std::string labelToLookup){
    std::string tempAddress;
    std::list<Label*>::const_iterator it;

    for (it = labelTable.begin(); it != labelTable.end(); ++it){
        if((*it)->labelName == labelToLookup){
            tempAddress = convertToBinaryString((*it)->address);
            return tempAddress;
        }
    }
}

bool Assembler::loadLabels2(std::string fileName){
    std::fstream fStr;
    fStr.open(fileName.c_str());
    std::string currentLine;
    Label* tempLabel = NULL;
    bool newLabel = false;

    std::cout << "Adding declared variables to the table." << std::endl;
    while(!fStr.eof()){
        std::getline(fStr, currentLine);
        currentLine = cleanString(currentLine);
        if(!currentLine.empty()){
            //stripped file, populate declared variables in label table
            if(currentLine[0] == '@' && isalpha(currentLine[1])){
                currentLine.erase(currentLine.begin());

                tempLabel = new Label();
                tempLabel->labelName = currentLine;
                tempLabel->address = 0; //initialized in the check
                newLabel = checkLabel(tempLabel);

                if(newLabel == false){
                    delete tempLabel; //frees memory if the label already exists
                }
            }

        }
        else{

        }
    }
    fStr.close();
}

void Assembler::resetStrings(){
    dest = "";
    jump = "";
    comp = "";
    binaryOut = "";
}

std::string Assembler::convertToBinaryString(int intToConvert){
    std::string tempString = "";
    std::string addZero = "";
    std::string binaryValue = "";
    int a;
    int b = intToConvert;
    bool startBinary = false;

    while(b > 0){
        a = b % 2;
        b = b / 2;
        if(a == 1){
            tempString += '1';
        }else{
            tempString += '0';
        }
    }
    int numberOfBits = 15 - tempString.length();
    //adds the padded zeros with the string
    for(int i = 0; i < numberOfBits; i++){
        addZero = addZero + '0';
    }

    binaryValue = addZero;

    for(int i = tempString.length() -1; i >= 0; i--){
        binaryValue += tempString[i];
    }

    return binaryValue;
}

void Assembler::printLabelTable(){
    std::list<Label*>::const_iterator it;
    for (it = labelTable.begin(); it != labelTable.end(); ++it){
        std::cout << (*it)->labelName << "  " << (*it)->address << std::endl;
    }
}

bool Assembler::checkLabel(Label* tempLabel){
    int currentAddress = -5; //starting address space for labels/variables, minus offset for duplicate addresses
    int maxAddress = 16383; //16384 starts Screen Addresses
    bool isNewLabel = true;

    //iterate through entire list to make sure label doesn't exist
    std::list<Label*>::const_iterator it;
    for (it = labelTable.begin(); it != labelTable.end(); ++it) {
        //makes sure we only check addresses
        if((*it)->address <= maxAddress){
            //label is within memory ranges
            if((*it)->labelName == tempLabel->labelName){
                //label is duplicates
                isNewLabel = false;
            }else{
                currentAddress++;
            }
        }

    }

    if(isNewLabel){
        tempLabel->address = currentAddress;
        std::cout << currentAddress << std::endl << std::endl;
        labelTable.push_back(tempLabel);
    }

    return isNewLabel;

}

std::string Assembler::cleanString(std::string& input){
  input.erase(std::remove(input.begin(),input.end(),' '),input.end());
  //parse comments out as well
  //while loop to find '/' and copy int value for location
  //then for loop backwards erasing until the '/' is erased
  std::string::iterator comment;
  int i = 0;
  for ( std::string::iterator it = input.begin(); it != input.end(); ++it, i++){

        if(input[i] == '/'){
            //if(!input.empty()){
              if( i + 1 < input.length()){
                  if(input[i + 1] == '/'){
                      comment = it;
                      break;
                  }
              }
            //}
        }
  }
  //clean up the comments

  input.erase(i, input.length());

  return input;
}
