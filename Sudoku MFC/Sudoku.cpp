#include "pch.h"
#include "Sudoku.h"

Sudoku::~Sudoku()
{
	delete[] fields;
	delete[] editFields;
}

bool Sudoku::Init()
{
	fields = new char[WIDTH * HEIGHT];
	if (fields == nullptr)
	{
		AfxMessageBox(L"Error allocating memory for fields!");
		return false;
	}

	editFields = new char[WIDTH * HEIGHT];
	if (editFields == nullptr)
	{
		AfxMessageBox(L"Error allocating memory for edit fields!");
		return false;
	}

	for (int i = 0; i < WIDTH * HEIGHT; i++)
	{
		fields[i] = '0';
		editFields[i] = '0';
	}

	currentFileData = 
	{
		"", "", Difficulty::Unknown
	};

	return true;
}

void Sudoku::SetField(Vec2 position, char number)
{
	fields[WIDTH * position.y + position.x] = number;
}

int Sudoku::GetField(Vec2 position)
{
	return fields[WIDTH * position.y + position.x];
}

void Sudoku::SetEditField(Vec2 position, char number)
{
	editFields[WIDTH * position.y + position.x] = number;
}

int Sudoku::GetEditField(Vec2 position)
{
	return editFields[WIDTH * position.y + position.x];
}

char* Sudoku::GetFields()
{
	return fields;
}

void Sudoku::FillFieldBuffer(char* buffer)
{
	for (int i = 0; i < WIDTH * HEIGHT; i++)
	{
		fields[i] = buffer[i];
	}
}

char* Sudoku::GetEditFields()
{
	return editFields;
}

void Sudoku::ClearSudoku()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (GetEditField(Vec2(x, y)) == '1') //wenn editierbar
			{
				SetField(Vec2(x, y), '0'); //auf leeres feld zurücksetzen
			}
		}
	}
}

int Sudoku::GetBufferLength()
{
	return WIDTH * HEIGHT;
}

bool Sudoku::LoadFromFile(std::string original, std::string save, Difficulty difficulty)
{
	std::ifstream saveFile(save);
	if (!saveFile) 
	{
		AfxMessageBox(L"Error loading save file!");
		return false;
	}

	char temp;
	int n = 0;
	while (saveFile.get(temp)) 
	{
		if (temp != '\n') 
		{
			fields[n++] = temp;
		}
	}
	saveFile.close();

	n = 0;
	std::ifstream originalFile(original);
	if (!originalFile) 
	{
		AfxMessageBox(L"Error loading original file!");
		return false;
	}

	while (originalFile.get(temp)) 
	{
		if (temp != '\n') 
		{
			editFields[n++] = (temp == '0' ? '1' : '0');
		}
	}
	originalFile.close();

	currentFileData = 
	{
		original,
		save,
		difficulty
	};

	return true;
}

bool Sudoku::SaveToFile(std::string save)
{
	std::ofstream saveFile(save);
	if (!saveFile) 
	{
		AfxMessageBox(L"Error saving sudoku!");
		return false;
	}

	for (int i = 0; i < WIDTH * HEIGHT; ++i) 
	{
		if (i % 9 == 0) 
		{
			saveFile << '\n';
		}
		saveFile << fields[i];
	}

	saveFile.close();
	return true; 
}
