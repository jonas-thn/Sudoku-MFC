#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "Vec2.h"

struct EmptyField
{
	Vec2 position;
	char number;
	int startNumber;
};

class Solver
{
public:
	Solver() = default;
	~Solver() = default;

	bool Init(std::string original);
	void SetField(const Vec2& position, char number);
	char GetField(const Vec2& position);
	char* GetBuffer();

	bool NumberInRow(int row, char number);
	bool NumberInColumn(int column, char number);
	bool NumberIn3x3(const Vec2& position, char number);

	bool CanPlaceNumber(const Vec2& position, char number);

	int FindEmptyFields();

	bool SolveSudoku();

private:
	const int WIDTH = 9;
	const int HEIGHT = 9;
	const int BOX = 3;

	std::vector<EmptyField> emptyFields;
	char* fields = nullptr;
};

