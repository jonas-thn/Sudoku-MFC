#include "pch.h"
#include "Generator.h"


bool Generator::Init()
{
	//Random::Seed();

    if (!solver.Init("./sudokus/GeneratorTemplate.txt"))
    {
        return false;
    }
    
    fields = solver.GetBuffer();

    return true;
}

void Generator::SetField(const Vec2& position, char number)
{
	fields[position.y * WIDTH + position.x] = number;
}

char Generator::GetField(const Vec2& position) const
{
	return fields[position.y * WIDTH + position.x];
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

		for (int i = 0; i < numToDelete;i++) 
		{
			int x = Random::GetInstance().Range(0, 8);
			int y = Random::GetInstance().Range(0, 8);
			if (GetField(Vec2(x, y)) != '0')
			{
				SetField(Vec2(x, y), '0');
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
			char element = Random::GetInstance().Char1To9();
			int x = Random::GetInstance().Range(0, 8);
			int y = Random::GetInstance().Range(0, 8);

			if (solver.CanPlaceNumber(Vec2(x, y), element))
			{
				SetField(Vec2(x, y), element);
			}
		}

		success = solver.SolveSudoku();
	}
}


