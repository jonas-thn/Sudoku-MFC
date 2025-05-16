#include "pch.h"
#include "Solver.h"

Solver::~Solver()
{
	delete[] fields;
}

void Solver::Init(const std::string& original)
{
	fields = new char[WIDTH * HEIGHT];

	if (!fields)
	{
		throw MemoryAllocationException("Error allocating memory for fields!");
	}

	std::ifstream file(original);
	if (!file)
	{
		throw FileStreamException("Error loading solver file!");
	}

	char temp;
	int n = 0;
	while (file.get(temp))
	{
		if (temp != '\n')
		{
			fields[n++] = temp;
		}
	}
	file.close();
}

void Solver::SetField(const Vec2& position, char number)
{
	fields[position.y * WIDTH + position.x] = number;
}

char Solver::GetField(const Vec2& position) const
{
	return fields[position.y * WIDTH + position.x];
}

char* Solver::GetBuffer()
{
	return fields;
}

void Solver::Clear()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			SetField(Vec2(x, y), '0');
		}
	}
}

void Solver::SetField(const int index, char number)
{
	fields[index] = number;
}

char Solver::GetField(const int index) const
{
	return fields[index];
}

bool Solver::NumberInRow(int row, char number) const
{
	for (int x = 0; x < WIDTH; x++)
	{
		if (number == GetField(Vec2( x, row )))
		{
			return true; 
		}
	}

	return false;
}

bool Solver::NumberInColumn(int column, char number) const
{
	for (int y = 0; y < HEIGHT; y++)
	{
		if (number == GetField(Vec2(column, y)))
		{
			return true;
		}
	}

	return false;
}

bool Solver::NumberIn3x3(const Vec2& position, char number) const
{
	int xBox = position.x / (int)BOX; 
	int yBox = position.y / (int)BOX; 

	int xStart = xBox * BOX; 
	int yStart = yBox * BOX;

	for (int y = 0; y < BOX; y++)
	{
		for (int x = 0; x < BOX; x++)
		{
			char element = GetField(Vec2(xStart + x, yStart + y));	

			if (element == number)			
			{
				return true;
			}
		}
	}

	return false; 
}

bool Solver::CanPlaceNumber(const Vec2& position, char number) const
{
	bool rowTest = !NumberInRow(position.y, number); 
	bool columnTest = !NumberInColumn(position.x, number); 
	bool boxTest = !NumberIn3x3(position, number); 

	return (rowTest && columnTest && boxTest);
}

int Solver::FindEmptyFields()
{
	emptyFields.clear();

	int count = 0;

	for (int y = 0; y < HEIGHT; y++) 
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (GetField(Vec2(x, y)) == '0')
			{
				EmptyField tempField = { Vec2(x, y), '0', 1 };
				emptyFields.push_back(tempField);
				count++;
			}
		}
	}

	return count;
}

bool Solver::SolveSudoku()
{
	int fieldsToTest = FindEmptyFields(); 

	int index = 0;

	while (index >= 0 && index < fieldsToTest)
	{
		EmptyField fieldTemp = emptyFields[index]; 

		int startNumberTemp = fieldTemp.startNumber;
		bool found = false; 

		for (int testNumber = fieldTemp.startNumber; testNumber <= 9; testNumber++)
		{
			char numToChar = (char)(testNumber + '0');
			if (CanPlaceNumber(fieldTemp.position, numToChar)) 
			{
				SetField(fieldTemp.position, numToChar); 

				EmptyField newField = { fieldTemp.position, numToChar, testNumber + 1 };
				emptyFields[index] = newField; 

				index++;
				found = true;
				break;
			}
		}

		if (!found) 
		{
			SetField(fieldTemp.position, '0'); 
			EmptyField undoField = { fieldTemp.position, '0', 1 }; 
			emptyFields[index] = undoField;

			index--;
		}
	}
	
	return (index < 0 ? false : true);
}
