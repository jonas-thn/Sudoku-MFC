#pragma once
#include "Vec2.h"
#include <string>
#include <fstream>
#include <iostream>
#include <map>

enum class Difficulty : int
{
	Easy,
	Medium,
	Hard,
	Impossible,
	Generated
};

struct FileData
{
	std::string original;
	std::string save;
	Difficulty difficulty;
};

class Sudoku
{
public:
	Sudoku() = default;
	~Sudoku();
	bool Init(Difficulty difficulty);

	void SetField(Vec2 position, char number);
	int GetField(Vec2 position);

	void SetEditField(Vec2 position, char number);
	int GetEditField(Vec2 position);

	char* GetFields();
	void FillFieldBuffer(char* buffer);

	char* GetEditFields();
	void ClearSudoku();
	int GetBufferLength();

	bool LoadFromFile();
	bool SaveToFile();

	void LoadFileData(Difficulty difficulty);	

private:
	const int WIDTH = 9;
	const int HEIGHT = 9;

	char* fields = nullptr;
	char* editFields = nullptr;
	FileData currentFileData;
};

