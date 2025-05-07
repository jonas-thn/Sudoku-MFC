#include "pch.h"
#include "UserInterface.h"


bool UserInterface::Init(char* fields)
{
	if (!sudokuBackground.Load("./sprites/sudoku.bmp", CSize(450, 200)))
	{
		AfxMessageBox(L"Error loading sudoku background!");
		return false;
	}
	sudokuBackground.SetZ(0);

	framebuffer.Load("./sprites/sudoku.bmp");

	spriteList.SetWorkspace(&framebuffer);

	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			spriteMap.push_back(SpriteData(nullptr, Vec2(x, y), 0));

			char field = fields[9 * y + x];
			int index = x + (y * 9);
			int number = field - '0'; 
			if (number == 0)
			{
				spriteMap.at(index) = SpriteData(nullptr, Vec2(x, y), number);
				continue;
			}

			CSprite* numberSprite = LoadNumberSprite(number);
			spriteMap.at(index) = SpriteData(numberSprite, Vec2(x, y), number);
			numberSprite->SetPosition(x * tileDimension.x + offsets.x, y * tileDimension.y + offsets.y);
		}
	}

	spriteList.Insert(&sudokuBackground);

	return true;
}

CSpriteList& UserInterface::GetSpriteList()
{
	return spriteList;
}

void UserInterface::SetField(Vec2 position, char number)
{
	CSprite* numberSprite = LoadNumberSprite(number - '0');
	CSprite* existingSprite = GetSpriteFromPosition(position);
	if (existingSprite != nullptr)
	{
		spriteList.Remove(existingSprite);
	}
	int index = position.x + (position.y * 9);
	spriteMap.at(index) = SpriteData(numberSprite, position, number);
	numberSprite->SetPosition(position.x * tileDimension.x + offsets.x, position.y * tileDimension.y + offsets.y);
}

CSprite* UserInterface::LoadNumberSprite(int number)
{
	std::string numberPath = "./sprites/" + std::to_string(number) + ".bmp"; //Load() akzeptiert kein const char*, sondern nur char* 
	std::vector<char> path(numberPath.begin(), numberPath.end());
	path.push_back('\0');

	CSprite* numberSprite = new CSprite();
	if (!numberSprite->Load(path.data(), CSize(40, 40)))
	{
		delete numberSprite;
		AfxMessageBox(L"Error loading number sprite!");
		return nullptr;
	}
	numberSprite->SetZ(10);
	numberSprite->SetPosition(-100, -100);
	spriteList.Insert(numberSprite);
	return numberSprite;
}

CSprite* UserInterface::GetSpriteFromPosition(Vec2 position)
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



