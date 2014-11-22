#include "Nafta.h"
#include <iostream>
#include <fstream>


Nafta::Nafta(std::string aFile, std::string pFile, float gdpPercentage){
    initialize(aFile, pFile, gdpPercentage);
}

void Nafta::initialize(std::string aFile, std::string pFile, float gdpPercentage){
    this->gdpPercentage = gdpPercentage;

    std::ifstream fileRead;

    //read in A file and setup exchange
    fileRead.open(aFile.c_str());
    if(fileRead.is_open()){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                fileRead >> exchange[i][j];
            }
        }
    }else{
        std::cout << aFile << " could not be opened successfully." << std::endl;
    }

    fileRead.close();

    //read in p file and setup initial price
    fileRead.open(pFile.c_str());
    if(fileRead.is_open()){
        for(int i = 0; i < 3; i++){
            fileRead >> price[i];
            //copies the initial price into old price for calculations
            oldPrice[i] = price[i];
            newPrice[i] = 0; //initializes variables for use
        }

    }else{
        std::cout << pFile << " could not be opened successfully." << std::endl;
    }

    fileRead.close();
    //copy initial price into old price

    //initialize new price to 0



}

void Nafta::markov(int months){
    //starts with 1 month, and offsets counter accordingly
    printStats();

    for(int i = 1; i < months + 1; i++){
        markov();
        if( (i % 12) == 0){
            //year has completed, increase GDP by  gdpValue
            increaseGDP();
        }
    }
        printStats();
}

void Nafta::increaseGDP(){
    for(int i = 0; i < 3; i++){
        oldPrice[i] = oldPrice[i] * gdpPercentage;
    }
}

void Nafta::markov(){

        for(int j = 0; j < 3; j++){
            //for each row in the exchange matrix
            newPrice[j] = 0; //prepares the new price matrix for matrix multiplication results
            for(int k = 0; k < 3; k++){
                //for each column in the exchange matrix
                newPrice[j] = newPrice[j] +  (exchange[j][k] * oldPrice[k]); //matrix multiplication for new price entry
            }
        }


    //old price equals the new price

    for(int i = 0; i < 3; i++){
        oldPrice[i] = newPrice[i];
    }
}

void Nafta::printStats(){
    std::cout << std::endl << "Current Markov Chain Price Vector is" << std::endl << std::endl;

    for(int i = 0; i < 3; i++){
        std::cout << oldPrice[i]  << std::endl;
    }
}
