#pragma once

#include "Random.h"
#include "Solver.h"
#include <string>
#include "Vec2.h"

class Generator
{
public:
	Generator() = default;
	~Generator() = default;

	bool Init();

	void SetField(const Vec2& position, char number);
	char GetField(const Vec2& position) const;

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

