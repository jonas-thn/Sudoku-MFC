#pragma once
#include <cstdlib>
#include <ctime>

class Random 
{
public:
    //singleton damit seed automatisch initialisiert wird
    static Random& GetInstance()
    {
		static Random instance; 
		return instance;       
    }

	//min and max inklusive
    int Range(int min, int max) 
    {
        return min + std::rand() % (max - min + 1);
    }

    char Char1To9()
    {
		int random = Range(1, 9);
        char numToChar = (char)(random + '0');

        return numToChar;
    }

private:
    Random()
    {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }

    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;
};