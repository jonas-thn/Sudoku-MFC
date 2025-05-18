#include "pch.h"
#include "Solver.h"

//dynamischen Speicher freigeben
Solver::~Solver()
{
	delete[] fields;
}

//Löser mit Datei-Feldern initialisieren
void Solver::Init(const std::string& original)
{
	if (fields)
	{
		delete[] fields;
	}

	fields = new char[WIDTH * HEIGHT];

	if (!fields)
	{
		throw MemoryAllocationException("Error allocating memory for fields!");
	}

	std::ifstream file(original);
	if (!file)
	{
		throw FileStreamException("Error loading solver file!");
	}

	char temp;
	int n = 0;
	while (file.get(temp))
	{
		if (temp != '\n')
		{
			fields[n++] = temp;
		}
	}
	file.close();
}

void Solver::SetField(const Vec2& position, char number)
{
	fields[position.y * WIDTH + position.x] = number;
}

char Solver::GetField(const Vec2& position) const
{
	return fields[position.y * WIDTH + position.x];
}

char* Solver::GetBuffer()
{
	return fields;
}

void Solver::Clear()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			SetField(Vec2(x, y), '0');
		}
	}
}

void Solver::SetField(const int index, char number)
{
	fields[index] = number;
}

char Solver::GetField(const int index) const
{
	return fields[index];
}

//Prüfen ob Nummer in Reihe
bool Solver::NumberInRow(int row, char number) const
{
	for (int x = 0; x < WIDTH; x++)
	{
		if (number == GetField(Vec2( x, row )))
		{
			return true; 
		}
	}

	return false;
}

//Prüfen ob Nummer in Spalte
bool Solver::NumberInColumn(int column, char number) const
{
	for (int y = 0; y < HEIGHT; y++)
	{
		if (number == GetField(Vec2(column, y)))
		{
			return true;
		}
	}

	return false;
}

//Prüfen ob Nummer in Quadrat
bool Solver::NumberIn3x3(const Vec2& position, char number) const
{
	//durch BOX teilen (abgerundet) und wieder mit BOX multiplizieren um lokalen 0,0 index von box zu erhalten
	int xBox = position.x / (int)BOX; 
	int yBox = position.y / (int)BOX; 
	int xStart = xBox * BOX; 
	int yStart = yBox * BOX;

	//3x3 Feld mit doppelter for-Schleife prüfen
	for (int y = 0; y < BOX; y++)
	{
		for (int x = 0; x < BOX; x++)
		{
			char element = GetField(Vec2(xStart + x, yStart + y));	

			if (element == number)			
			{
				return true;
			}
		}
	}

	return false; 
}

//Reihe, Spalte und Quadrat Test zusammenfügen
bool Solver::CanPlaceNumber(const Vec2& position, char number) const
{
	bool rowTest = !NumberInRow(position.y, number); 
	bool columnTest = !NumberInColumn(position.x, number); 
	bool boxTest = !NumberIn3x3(position, number); 

	return (rowTest && columnTest && boxTest);
}

//Alle leeren Felder von Sudoku finden, relevant für Löser
int Solver::FindEmptyFields()
{
	emptyFields.clear();

	int count = 0;

	for (int y = 0; y < HEIGHT; y++) 
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (GetField(Vec2(x, y)) == '0')
			{
				EmptyField tempField = { Vec2(x, y), '0', 1 };
				emptyFields.push_back(tempField);
				count++;
			}
		}
	}

	return count;
}

//Sudoku lösen
bool Solver::SolveSudoku()
{
	//leere Felder + Anzahl finden
	int fieldsToTest = FindEmptyFields(); 

	int index = 0;

	//alle leeren Felder durchgehen
	while (index >= 0 && index < fieldsToTest)
	{
		EmptyField fieldTemp = emptyFields[index]; 

		int startNumberTemp = fieldTemp.startNumber;
		bool found = false; 

		//alle Zahlen durchgehen
		for (int testNumber = fieldTemp.startNumber; testNumber <= 9; testNumber++)
		{
			//teste ob aktuelle Zahl möglich
			char numToChar = (char)(testNumber + '0');
			if (CanPlaceNumber(fieldTemp.position, numToChar)) 
			{
				//Feld setzen
				SetField(fieldTemp.position, numToChar); 

				//Test Nummer für nächsten Durchgang erhöhen
				EmptyField newField = { fieldTemp.position, numToChar, testNumber + 1 };
				emptyFields[index] = newField; 
#
				//nächstes Feld betrachten
				index++;
				found = true;
				break;
			}
		}

		//keine Zahl möglich
		if (!found) 
		{
			//Feld zurücksetzen
			SetField(fieldTemp.position, '0'); 
			//Test Nummer nur von diesem Feld auf 1 zurücksetzen
			EmptyField undoField = { fieldTemp.position, '0', 1 }; 
			emptyFields[index] = undoField;

			//vorheriges Feld betrachten
			index--;
		}
	}
	
	//Rückgabe ob erfolgreich
	return (index < 0 ? false : true);
}
