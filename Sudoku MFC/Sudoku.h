#pragma once
#include "Vec2.h"
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include "CustomExceptions.h"

//Schwierigkeitsgrade
enum class Difficulty : int
{
	Easy,
	Medium,
	Hard,
	Impossible
};

//Pfade für die Sudoku-Dateien und Schwierigkeit
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

	//Sudoku Felder
	void SetField(const Vec2& position, char number);
	int GetField(const Vec2& position) const;
	char* GetFields();
	void FillFieldBuffer(char* buffer);
	void ClearSudoku();
	int GetBufferLength() const;

	//bearbeitbare Felder
	void SetEditField(const Vec2& position, char number);
	int GetEditField(const Vec2& position) const;
	char* GetEditFields();

	//Sudoku Datein laden / speichern
	void LoadFromFile();
	void SaveToFile();
	void SaveToFileOverrideOriginal();
	void LoadFileData(Difficulty difficulty);	
	FileData GetCurrentFileData() const;

private:
	const int WIDTH = 9;
	const int HEIGHT = 9;

	char* fields = nullptr;
	char* editFields = nullptr;
	FileData currentFileData;
};

