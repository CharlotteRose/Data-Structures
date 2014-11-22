#include "Nafta.h"



int main(){

    Nafta nafta("exchange.txt", "price.txt", 1.02);
    nafta.markov(612);


    return 0;
}
