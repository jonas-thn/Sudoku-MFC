#pragma once
#include "Vec2.h"
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include "CustomExceptions.h"

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

	void Init(Difficulty difficulty);

	void SetField(const Vec2& position, char number);
	int GetField(const Vec2& position) const;
	char* GetFields();

	void SetEditField(const Vec2& position, char number);
	int GetEditField(const Vec2& position) const;
	char* GetEditFields();

	void FillFieldBuffer(char* buffer);
	void ClearSudoku();
	int GetBufferLength() const;

	void LoadFromFile();
	void SaveToFile();

	void LoadFileData(Difficulty difficulty);	
	FileData GetCurrentFileData() const;

private:
	const int WIDTH = 9;
	const int HEIGHT = 9;

	char* fields = nullptr;
	char* editFields = nullptr;
	FileData currentFileData;
};

