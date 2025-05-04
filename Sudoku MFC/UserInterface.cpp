#include "pch.h"
#include "UserInterface.h"

bool UserInterface::InitUnserInerface()
{
	for (int i = 0; i < spritePoolSize; i++)
	{
		const int number = i % 9 + 1;
		std::string numberPath = "./sprites/" + std::to_string(number) + ".bmp"; //Load() akzeptiert kein const char*, sondern nur char* 
		std::vector<char> path(numberPath.begin(), numberPath.end());
		path.push_back('\0');
		if (!numberPool[i].Load(path.data(), CSize(40, 40)))
		{
			AfxMessageBox(L"Error loading number sprite!");
			return false;
		}
		numberPool[i].SetZ(10);
		numberPool[i].SetPosition(0, 0);
	}

	if (!sudokuBackground.Load("./sprites/sudoku.bmp", CSize(450, 200)))
	{
		AfxMessageBox(L"Error loading sudoku background!");
	}
	sudokuBackground.SetZ(0);

	framebuffer.Load("./sprites/sudoku.bmp");

	spriteList.SetWorkspace(&framebuffer);

	for (int i = 0; i < spritePoolSize; i++)
	{
		Vec2 coords = ConvertIndexToCoordinates(i);
		numberPool[i].SetPosition(coords.x, coords.y);	
		spriteList.Insert(&numberPool[i]);
	}
	spriteList.Insert(&sudokuBackground);

	return false;
}

CSpriteList& UserInterface::GetSpriteList()
{
	return spriteList;
}

Vec2 UserInterface::ConvertIndexToCoordinates(int index)
{
	int x = (index % 9) * tileDimension.x + offset;
	int y = (index / 9) * tileDimension.y + offset * 2;

	return Vec2(x, y);
}

void UserInterface::SetField(Vec2 position, int number)
{
	/*static int numberCounter[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	numberCounter[number - 1]++;*/
}
