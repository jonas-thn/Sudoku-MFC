#pragma once

#include "Random.h"
#include "Solver.h"
#include <string>

class Generator
{
public:
	Generator() = default;
	~Generator() = default;

	bool Init();

	void SetField(int x, int y, char number);
	char GetField(int x, int y);

	void ClearBuffer();
	char* GetBuffer();

	void GenerateSudoku(int difficulty);
	void GenerateFilledSudoku();

private:
	const int WIDTH = 9;
	const int HEIGHT = 9;
	const int BOX = 3;

	char* fields = nullptr;
	Solver solver;
};

