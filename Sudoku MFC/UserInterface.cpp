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
		numberPool[i].SetPosition(-100, -100);
	}

	if (!sudokuBackground.Load("./sprites/sudoku.bmp", CSize(450, 200)))
	{
		AfxMessageBox(L"Error loading sudoku background!");
		return false;
	}
	sudokuBackground.SetZ(0);

	framebuffer.Load("./sprites/sudoku.bmp");

	spriteList.SetWorkspace(&framebuffer);

	for (int i = 0; i < spritePoolSize; i++)
	{
		numberPool[i].SetPosition(-100, -100);
		spriteList.Insert(&numberPool[i]);
	}
	spriteList.Insert(&sudokuBackground);

	return true;
}

CSpriteList& UserInterface::GetSpriteList()
{
	return spriteList;
}

Vec2 UserInterface::ConvertIndexToCoordinates(int index)
{
	int x = (index % 9) * tileDimension.x + offsets.x;
	int y = (index / 9) * tileDimension.y + offsets.y;

	return Vec2(x, y);
}

void UserInterface::SetField(Vec2 position, char number)
{
}

void UserInterface::UpdateSudoku(char* fields)
{
	static int numberCounter[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			char field = fields[9 * y + x];
			int number = field - '0'; // Convert char to int
			if (number == 0)
			{
				continue;
			}

			int poolPosition = numberCounter[number - 1] * 9 + number - 1;
			numberPool[poolPosition].SetPosition(x * tileDimension.x + offsets.x, y * tileDimension.y + offsets.y);
			numberCounter[number - 1]++;
		}
	}
}

//bool UserInterface::LoadNumberSprite(int number)
//{
//	std::string numberPath = "./sprites/" + std::to_string(number) + ".bmp"; //Load() akzeptiert kein const char*, sondern nur char* 
//	std::vector<char> path(numberPath.begin(), numberPath.end());
//	path.push_back('\0');
//
//	CSprite numberSprite;
//	if (numberSprite.Load(path.data(), CSize(40, 40)))
//	{
//		AfxMessageBox(L"Error loading number sprite!");
//		return false;
//	}
//	numberSprite.SetZ(10);
//	numberPool[i].SetPosition(-100, -100);
//}



