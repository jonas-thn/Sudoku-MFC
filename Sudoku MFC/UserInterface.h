#pragma once
#include "spritelib.h"
#include <string>
#include <vector>
#include "Vec2.h"

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

	bool InitUnserInerface(char* fields);
	CSpriteList& GetSpriteList();
	void SetField(Vec2 position, char number);
	CSprite* LoadNumberSprite(int number);

	CSprite* GetSpriteFromPosition(Vec2 position);

private:
	CSprite sudokuBackground;
	CDIB framebuffer;

	const Vec2 tileDimension = Vec2(50, 47);
	const Vec2 offsets = Vec2(5, 10);
	CSpriteList spriteList;
	std::vector<SpriteData> spriteMap;
};

