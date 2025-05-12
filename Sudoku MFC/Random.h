#pragma once
#include <cstdlib>
#include <ctime>

class Random 
{
public:
    static Random& GetInstance()
    {
		static Random instance; 
		return instance;       
    }

    void Seed()
    {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }

	//min and max inclusive
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
    Random() = default;
};