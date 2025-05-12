#include "pch.h"
#include "Sudoku.h"

Sudoku::~Sudoku()
{
	delete[] fields;
	delete[] editFields;
}

bool Sudoku::Init(Difficulty difficulty)
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

	LoadFileData(difficulty);	

	return true;
}

void Sudoku::SetField(const Vec2& position, char number)
{
	fields[WIDTH * position.y + position.x] = number;
}

int Sudoku::GetField(const Vec2& position) const
{
	return fields[WIDTH * position.y + position.x];
}

void Sudoku::SetEditField(const Vec2& position, char number)
{
	editFields[WIDTH * position.y + position.x] = number;
}

int Sudoku::GetEditField(const Vec2& position) const
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

int Sudoku::GetBufferLength() const
{
	return WIDTH * HEIGHT;
}

bool Sudoku::LoadFromFile()
{
	std::string original = currentFileData.original;
	std::string save = currentFileData.save;

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

	return true;
}

bool Sudoku::SaveToFile()
{
	std::string save = currentFileData.save;

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

void Sudoku::LoadFileData(Difficulty difficulty)
{
	switch (difficulty)
	{
	case Difficulty::Easy:
		currentFileData = { "./sudokus/Sudoku1.txt", "./sudokus/Sudoku1_Save.txt", Difficulty::Easy };
		break;
	case Difficulty::Medium:
		currentFileData = { "./sudokus/Sudoku2.txt", "./sudokus/Sudoku2_Save.txt", Difficulty::Medium };
		break;
	case Difficulty::Hard:
		currentFileData = { "./sudokus/Sudoku3.txt", "./sudokus/Sudoku3_Save.txt", Difficulty::Hard };
		break;
	case Difficulty::Impossible:
		currentFileData = { "./sudokus/Sudoku4.txt", "./sudokus/Sudoku4_Save.txt", Difficulty::Impossible };
		break;
	case Difficulty::Generated:
		currentFileData = { "./sudokus/Sudoku5.txt", "./sudokus/Sudoku5_Save.txt", Difficulty::Generated };
		break;
	}
}

FileData Sudoku::GetCurrentFileData() const
{
	return currentFileData;
}
