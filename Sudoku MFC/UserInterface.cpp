#include "pch.h"
#include "UserInterface.h"

//Dynamischen Speicher löschen
UserInterface::~UserInterface()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			int index = x + (y * WIDTH);
			CSprite* existingSprite = spriteMap.at(index).sprite;
			if (existingSprite != nullptr)
			{
				spriteList.Remove(existingSprite);
				delete existingSprite;
			}
		}
	}
}

Vec2 UserInterface::ConvertPositionToCoordinates(const Vec2& position)
{
	//Sudoku -> Screen
	return Vec2(position.x * tileDimension.x, position.y * tileDimension.y);
}

Vec2 UserInterface::ConvertCoordinatesToPosition(const Vec2& coordinates)
{
	//Screen -> Sudoku
	return Vec2(coordinates.x / tileDimension.x, coordinates.y / tileDimension.y);
}

void UserInterface::Init(const char* fields, const char* editFields)
{
	//Undo zurücksetzen
	undo.ClearUndo();

	//Felder Liste vergrößern
	tempFieldBuffer.resize(WIDTH * HEIGHT);

	//framebuffer laden
	if(!framebuffer.Load("./sprites/white.bmp"))
	{
		throw SpriteLoadException("Error loading framebuffer!");
	}

	spriteList.SetWorkspace(&framebuffer);

	//Hintergrund laden und setzen
	if (!sudokuBackground.Load("./sprites/sudoku.bmp"))
	{
		throw SpriteLoadException("Error loading sudoku.bmp!");
	}
	sudokuBackground.SetZ(0);
	sudokuBackground.SetPosition(0, 0);
	spriteList.Insert(&sudokuBackground);

	//beaqrbeitbare Felder laden
	for (int i = 0; i < WIDTH * HEIGHT; i++)
	{
		editFieldBuffer.push_back(editFields[i]);
	}

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			//leere Sprite Daten laden
			spriteMap.push_back(SpriteData(nullptr, Vec2(x, y), 0));

			int index = x + (y * WIDTH);
			char field = fields[index];
			int number = field - '0'; 
			undo.AddUndo(Vec2(x, y), field);
			tempFieldBuffer.at(index) = field;
			if (number == 0)
			{
				//Leere Felder in SpriteMap eintragen
				spriteMap.at(index) = SpriteData(nullptr, Vec2(x, y), number);
				continue;
			}

			//Sprite laden
			CSprite* numberSprite = LoadNumberSprite(number);
			spriteMap.at(index) = SpriteData(numberSprite, Vec2(x, y), number);
			numberSprite->SetPosition(x * tileDimension.x + offsets.x, y * tileDimension.y + offsets.y);

			//bearbeitbare Felder transparent
			if (editFieldBuffer.at(index) == '1')
			{
				numberSprite->SetAlpha(0.6f);
			}
		}
	}

	//Umrandung laden
	border.Init(spriteList);
	border.SetPosition(Vec2(0, 0));
}

CSpriteList& UserInterface::GetSpriteList()
{
	return spriteList;
}

void UserInterface::SetField(const Vec2& position, char number, bool isUndo)
{
	//prüfen ob Feld bearbeitbar ist
	if ((editFieldBuffer.at(position.x + (position.y * WIDTH)) == '0'))
	{
		return;
	}

	//Sprite laden
	CSprite* numberSprite = LoadNumberSprite(number - '0');

	//Prüfen ob an der Stelle bereits Sprite existiert
	CSprite* existingSprite = GetSpriteFromPosition(position);
	if (existingSprite != nullptr)
	{
		//Sprite löschen
		spriteList.Remove(existingSprite);
		delete existingSprite;
	}

	//neue Sprite setzen
	int index = position.x + (position.y * WIDTH);
	spriteMap.at(index) = SpriteData(numberSprite, position, number);
	numberSprite->SetPosition(position.x * tileDimension.x + offsets.x, position.y * tileDimension.y + offsets.y);

	//bearbeitbare Felder transparent
	if (editFieldBuffer.at(index) == '1')
	{
		numberSprite->SetAlpha(0.6f);
	}

	//Undo hinzufügen
	if (!isUndo)
	{
		undo.AddUndo(position, tempFieldBuffer.at(index));
	}
	tempFieldBuffer.at(index) = number;
}

CSprite* UserInterface::LoadNumberSprite(int number)
{
	//Load() akzeptiert kein const char*, sondern nur char* 
	std::string numberPath = "./sprites/" + std::to_string(number) + ".bmp"; 
	std::vector<char> path(numberPath.begin(), numberPath.end());
	path.push_back('\0');

	//Sprite laden
	CSprite* numberSprite = new CSprite();
	if (!numberSprite->Load(path.data(), CSize(40, 40)))
	{
		delete numberSprite;
		throw SpriteLoadException("Error loading sprite: " + numberPath);
	}
	numberSprite->SetZ(10);
	numberSprite->SetPosition(-100, -100);
	spriteList.Insert(numberSprite);
	return numberSprite;
}

//Sprite von Sudoku Position abfragen
CSprite* UserInterface::GetSpriteFromPosition(const Vec2& position)
{
	for (const SpriteData& spriteData : spriteMap)
	{
		if (spriteData.position == position)
		{
			return spriteData.sprite;
		}
	}
	return nullptr;
}

//Umrandung setzen (von UserInerface)
void UserInterface::SetBorder(const Vec2& pos)
{
	lastMousePos = pos;
	if (lastMousePos.x < 0) { lastMousePos.x = 0; }
	if (lastMousePos.x > (WIDTH -1)) { lastMousePos.x = (WIDTH-1); }
	if (lastMousePos.y < 0) { lastMousePos.y = 0; }
	if (lastMousePos.y > (HEIGHT -1)) { lastMousePos.y = (HEIGHT-1); }
	border.SetPosition(lastMousePos);
}

Vec2 UserInterface::GetLastMousePos() const
{
	return lastMousePos;
}

//Jedes Feld im Sudoku aktualisieren
void UserInterface::CompleteUpdate(const char* fields)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			int index = x + (y * WIDTH);
			char field = fields[index];
			int number = field - '0';
			if (number == 0)
			{
				ClearField(Vec2(x, y));
				continue;
			}

			SetField(Vec2(x, y), field);
		}
	}
}

//Feld löschen
void UserInterface::ClearField(const Vec2& position, bool isUndo)
{
	CSprite* existingSprite = GetSpriteFromPosition(position);
	if (existingSprite != nullptr)
	{
		spriteList.Remove(existingSprite);
	}
	int index = position.x + (position.y * WIDTH);
	spriteMap.at(index) = SpriteData(nullptr, position, 0);

	if(!isUndo)
	{
		undo.AddUndo(position, tempFieldBuffer.at(index));
	}
	tempFieldBuffer.at(index) = '0';
}

char* UserInterface::GetTempFieldBuffer()
{
	return tempFieldBuffer.data();
}

//Undo auslösen
void UserInterface::TriggerUndo()
{
	UndoField undoField;
	if(undo.UndoLast(tempFieldBuffer.data(), undoField))
	{
		if (undoField.number == '0')
		{
			ClearField(Vec2(undoField.x, undoField.y), true);
		}
		else
		{
			SetField(Vec2(undoField.x, undoField.y), undoField.number, true);
		}
	}
}

void UserInterface::ClearUndo()
{
	undo.ClearUndo();
}

//Umrandung initialisieren
bool Border::Init(CSpriteList& spriteList)
{
	if (!borderLeft.Load("./sprites/border_v.bmp", CSize(4, 50), 0))
	{
		AfxMessageBox(L"Error loading border!");
		return false;
	}
	borderLeft.SetPosition(0, 0);
	borderLeft.SetZ(20);
	spriteList.Insert(&borderLeft);

	if (!borderRight.Load("./sprites/border_v.bmp", CSize(4, 50), 0))
	{
		AfxMessageBox(L"Error loading border!");
		return false;
	}
	borderRight.SetPosition(46, 0);
	borderRight.SetZ(20);
	spriteList.Insert(&borderRight);

	if (!borderTop.Load("./sprites/border_h.bmp", CSize(50, 4), 0))
	{
		AfxMessageBox(L"Error loading border!");
		return false;
	}
	borderTop.SetPosition(0, 0);
	borderTop.SetZ(20);
	spriteList.Insert(&borderTop);

	if (!borderBottom.Load("./sprites/border_h.bmp", CSize(50, 4), 0))
	{
		AfxMessageBox(L"Error loading border!");
		return false;
	}
	borderBottom.SetPosition(0, 46);
	borderBottom.SetZ(20);
	spriteList.Insert(&borderBottom);
}

//Umrandung setzen
void Border::SetPosition(Vec2 position)
{
	borderLeft.SetPosition(position.x * tileDimension.x + offsets.x, position.y * tileDimension.y + offsets.y);
	borderRight.SetPosition(position.x * tileDimension.x + 46 + offsets.x, position.y * tileDimension.y + offsets.y);
	borderTop.SetPosition(position.x * tileDimension.x + offsets.x, position.y * tileDimension.y + offsets.y);
	borderBottom.SetPosition(position.x * tileDimension.x + offsets.x, position.y * tileDimension.y + 46 + offsets.y);
}

