#pragma once
#include "spritelib.h"
#include <string>
#include <vector>
#include "Vec2.h"
#include <algorithm>

struct Border
{
	Border() = default;
	bool Init(CSpriteList& spriteList);
	void SetPosition(Vec2 position);	
	
private:
	CSprite borderLeft;
	CSprite borderRight;
	CSprite borderTop;
	CSprite borderBottom;

	Vec2 position = Vec2(0, 0);
	Vec2 tileDimension = Vec2(49, 47);
	Vec2 offsets = Vec2(5, 5);
};

struct SpriteData
{
	SpriteData(CSprite* sprite, Vec2 position, int number)
		: sprite(sprite), position(position), number(number) { }

	CSprite* sprite;
	Vec2 position;
	int number;
};

class UserInterface
{
public:
	UserInterface() = default;
	~UserInterface() = default;

	bool Init(char* fields);
	CSpriteList& GetSpriteList();
	void SetField(Vec2 position, char number);
	CSprite* LoadNumberSprite(int number);

	CSprite* GetSpriteFromPosition(Vec2 position);

	Border border;
	CDIB framebuffer;
private:
	CSprite sudokuBackground;

	const Vec2 tileDimension = Vec2(50, 47);
	const Vec2 offsets = Vec2(5, 10);
	CSpriteList spriteList;
	std::vector<SpriteData> spriteMap;
};

