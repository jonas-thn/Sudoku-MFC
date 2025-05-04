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
	void SetField(Vec2 position, int number);
	void ClearField(Vec2 position);

private:
	CSprite sudokuBackground;
	CDIB framebuffer;

	const Vec2 tileDimension = Vec2(50, 47);
	const int offset = 5;
	const int spritePoolSize = 81;
	CSprite numberPool[81];
	CSpriteList spriteList;
};

