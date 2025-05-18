#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "Vec2.h"
#include "CustomExceptions.h"

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
	~Solver();

	//Sudoku Felder
	void Init(const std::string& original);
	void SetField(const Vec2& position, char number);
	char GetField(const Vec2& position) const;
	void SetField(const int index, char number);
	char GetField(const int index) const;
	char* GetBuffer();
	void Clear();

	//Prüfen ob Nummer in Zeile/Spalte/Quadrat
	bool NumberInRow(int row, char number) const;
	bool NumberInColumn(int column, char number) const;
	bool NumberIn3x3(const Vec2& position, char number) const;
	bool CanPlaceNumber(const Vec2& position, char number) const;

	//Sudoku lösen
	int FindEmptyFields();
	bool SolveSudoku();

private:
	const int WIDTH = 9;
	const int HEIGHT = 9;
	const int BOX = 3;

	std::vector<EmptyField> emptyFields;
	char* fields = nullptr;
};

