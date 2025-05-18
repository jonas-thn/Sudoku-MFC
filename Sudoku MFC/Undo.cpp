#include "pch.h"
#include "Undo.h"

void Undo::AddUndo(Vec2 position, char number)
{
	//Undo Feld in Stack hinzuf�gen
	UndoField undoField = { position.x, position.y, number };
	undoStack.push_back(undoField);
}

bool Undo::UndoLast(char* fields, UndoField& undoField)
{
	//letzten Zug zur�cksetzen wenn er existiert
	if (!undoStack.empty())
	{
		UndoField lastUndo = undoStack.back();
		fields[lastUndo.y * 9 + lastUndo.x] = lastUndo.number;
		undoStack.pop_back();
		undoField.x = lastUndo.x;
		undoField.y = lastUndo.y;
		undoField.number = lastUndo.number;
		return true;
	}
	return false;
}

void Undo::ClearUndo()
{
	undoStack.clear();
}
