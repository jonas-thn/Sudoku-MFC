#pragma once
#include "Vec2.h"
#include <string>
#include <fstream>
#include <iostream>

class Sudoku
{
public:
	Sudoku() = default;
	~Sudoku();
	bool Init();

	void SetField(Vec2 position, char number);
	int GetField(Vec2 position);

	void SetEditField(Vec2 position, char number);
	int GetEditField(Vec2 position);

	char* GetFields();
	void FillFieldBuffer(char* buffer);

	char* GetEditFields();
	void ClearSudoku();
	int GetBufferLength();

	bool LoadFromFile(std::string original, std::string save);
	bool SaveToFile(std::string save);

private:
	const int WIDTH = 9;
	const int HEIGHT = 9;
	const int QUAD = 3;

	char* fields = nullptr;
	char* editFields = nullptr;
};

