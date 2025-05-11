#pragma once
#include <cstdlib>
#include <ctime>

class Random 
{
public:
    static void Seed()
    {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }

	//min and max inclusive
    static int Range(int min, int max) 
    {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        return min + std::rand() % (max - min + 1);
    }

    static char Char1To9()
    {
		int random = Range(1, 9);
        char numToChar = (char)(random + '0');

        return numToChar;
    }
};