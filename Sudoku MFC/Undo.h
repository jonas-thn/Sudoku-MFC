#pragma once
#include <vector>
#include "Vec2.h"

struct UndoField
{
	int x;
	int y;
	char number;
};

class Undo
{
public:
	Undo() = default;
	~Undo() = default;

	void AddUndo(Vec2 position, char number);
	bool UndoLast(char* fields, UndoField& undoField);
	void ClearUndo();

private:
	std::vector<UndoField> undoStack;
};

