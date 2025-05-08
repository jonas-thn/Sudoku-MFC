#pragma once

#include <vector>
#include <string>
#include <fstream>

struct EmptyField
{
	int x;
	int y;
	char number;
	int startNumber;
};

class Solver
{
public:
	Solver() = default;
	~Solver() = default;

	bool Init(std::string original);
	void SetField(int x, int y, char number);
	char GetField(int x, int y);
	char* GetBuffer();

	bool NumberInRow(int row, char number);
	bool NumberInColumn(int column, char number);
	bool NumberIn3x3(int x, int y, char number);

	bool CanPlaceNumber(int x, int y, char number);

	int FindEmptyFields();

	bool SolveSudoku();

private:
	const int WIDTH = 9;
	const int HEIGHT = 9;
	const int BOX = 3;

	std::vector<EmptyField> emptyFields;
	char* fields = nullptr;
};

