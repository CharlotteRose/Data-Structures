#ifndef NAFTA
#define NAFTA
#include <string>
#include <vector>

class Nafta{
public:
    Nafta(std::string aFile, std::string pFile, float gdpPercentage);
    void initialize(std::string aFile, std::string pFile, float gdpPercentage);
    void markov(int months);
    void increaseGDP();
    void markov();
    void printStats();

private:
    float exchange[3][3];
    float price[3];
    float oldPrice[3];
    float newPrice[3];
    float gdpPercentage;





};

#endif // NAFTA
