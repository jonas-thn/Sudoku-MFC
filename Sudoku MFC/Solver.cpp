#include "pch.h"
#include "Solver.h"

bool Solver::Init(std::string original)
{
	fields = new char[WIDTH * HEIGHT];
	
	if (!fields)
	{
		AfxMessageBox(L"Error allocating memory for fields!");
		return false;
	}

	std::ifstream file(original);
	if (!file)
	{
		AfxMessageBox(L"Error loading solver file!");
		return false;
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

void Solver::SetField(int x, int y, char number)
{
	fields[y * WIDTH + x] = number;
}

char Solver::GetField(int x, int y)
{
	return fields[y * WIDTH + x];
}

char* Solver::GetBuffer()
{
	return fields;
}

bool Solver::NumberInRow(int row, char number)
{
	for (int x = 0; x < WIDTH; x++)
	{
		if (number == GetField(x, row)) 
		{
			return true; 
		}
	}

	return false;
}

bool Solver::NumberInColumn(int column, char number)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		if (number == GetField(column, y))
		{
			return true;
		}
	}

	return false;
}

bool Solver::NumberIn3x3(int x, int y, char number)
{
	int xBox = x / (int)BOX; 
	int yBox = y / (int)BOX; 

	int xStart = xBox * BOX; 
	int yStart = yBox * BOX;

	for (int y = 0; y < BOX; y++)
	{
		for (int x = 0; x < BOX; x++)
		{
			char element = GetField(xStart + x, yStart + y);	

			if (element == number)			
			{
				return true;
			}
		}
	}

	return false; 
}

bool Solver::CanPlaceNumber(int x, int y, char number)
{
	int rowTest = !NumberInRow(y, number); 
	int columnTest = !NumberInColumn(x, number); 
	int boxTest = !NumberIn3x3(x, y, number); 

	return (rowTest && columnTest && boxTest);
}

int Solver::FindEmptyFields()
{
	int count = 0;

	for (int y = 0; y < HEIGHT; y++) 
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (GetField(x, y) == '0') 
			{
				EmptyField tempField = { x, y, '0', 1 };
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
			if (CanPlaceNumber(fieldTemp.x, fieldTemp.y, numToChar)) 
			{
				SetField(fieldTemp.x, fieldTemp.y, numToChar); 

				EmptyField newField = { fieldTemp.x, fieldTemp.y, numToChar, testNumber + 1 };
				emptyFields[index] = newField; 

				index++;
				found = true;
				break;
			}
		}

		if (!found) 
		{
			SetField(fieldTemp.x, fieldTemp.y, '0'); 
			EmptyField undoField = { fieldTemp.x, fieldTemp.y, '0', 1 }; 
			emptyFields[index] = undoField;

			index--;
		}
	}
	
	return (index < 0 ? false : true);
}
