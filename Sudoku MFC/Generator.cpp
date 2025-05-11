#include "pch.h"
#include "Generator.h"


bool Generator::Init()
{
    Random::Seed();
    if (!solver.Init("./sudokus/GeneratorTemplate.txt"))
    {
        return false;
    }
    
    fields = solver.GetBuffer();

    return true;
}

void Generator::SetField(int x, int y, char number)
{
	fields[y * WIDTH + x] = number;
}

char Generator::GetField(int x, int y)
{
	return fields[y * WIDTH + x];
}

void Generator::ClearBuffer()
{
	for (int i = 0; i < WIDTH * HEIGHT; i++)
	{
		fields[i] = '0';
	}
}

char* Generator::GetBuffer()
{
    return fields;
}

void Generator::GenerateSudoku(int difficulty)
{
	GenerateFilledSudoku(); 

	char* tempBuffer1 = new char[WIDTH * HEIGHT];
	char* tempBuffer2 = new char[WIDTH * HEIGHT];

	for (int i = 0; i < WIDTH * HEIGHT; i++) 
	{
		tempBuffer2[i] = fields[i];
	}

	int numToDelete = 10 * difficulty;
	bool solvable = false;

	while (!solvable)
	{
		for (int i = 0; i < WIDTH * HEIGHT; i++) 
		{
			fields[i] = tempBuffer2[i];
		}

		for (int i = 0; i < numToDelete;) 
		{
			int x = Random::Range(0, 8);
			int y = Random::Range(0, 8); 
			if (GetField(x, y) != '0')
			{
				SetField(x, y, '0');
				i++;
			}
		}

		for (int i = 0; i < WIDTH * HEIGHT; i++) 
		{
			tempBuffer1[i] = fields[i];
		}

		solvable = solver.SolveSudoku();

		if (solvable)
		{
			for (int i = 0; i < WIDTH * HEIGHT; i++)
			{
				fields[i] = tempBuffer1[i];
			}
		}
	}

	delete[] tempBuffer1;
	delete[] tempBuffer2;
}

void Generator::GenerateFilledSudoku()
{
	int maxTries = 45;
	bool success = false;

	while (!success)
	{
		ClearBuffer();

		for (int i = 0; i < maxTries; i++)
		{
			char element = Random::Char1To9();
			int x = Random::Range(0, 8);
			int y = Random::Range(0, 8);

			if (solver.CanPlaceNumber(x, y, element))
			{
				SetField(x, y, element);
			}
		}

		success = solver.SolveSudoku();
	}
}


