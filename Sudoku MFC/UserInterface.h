#pragma once
#include "spritelib.h"
#include <string>
#include <vector>
#include "Vec2.h"



class UserInterface
{
public:
	UserInterface() = default;
	~UserInterface() = default;

	bool InitUnserInerface();
	CSpriteList& GetSpriteList();
	Vec2 ConvertIndexToCoordinates(int index);
	void SetField(Vec2 position, char number);
	void UpdateSudoku(char* fields);
	bool LoadNumberSprite(int number);

private:
	CSprite sudokuBackground;
	CDIB framebuffer;

	const Vec2 tileDimension = Vec2(50, 47);
	const Vec2 offsets = Vec2(5, 10);
	const int spritePoolSize = 81;
	CSprite numberPool[81];
	CSpriteList spriteList;
};

