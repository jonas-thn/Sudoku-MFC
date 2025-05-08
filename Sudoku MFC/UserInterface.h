#pragma once
#include "spritelib.h"
#include <string>
#include <vector>
#include "Vec2.h"
#include <algorithm>
#include "Undo.h"

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

	Vec2 ConvertPositionToCoordinates(Vec2 position);
	Vec2 ConvertCoordinatesToPosition(Vec2 coordinates);

	bool Init(char* fields);
	CSpriteList& GetSpriteList();
	void SetField(Vec2 position, char number, bool isUndo = false);
	CSprite* LoadNumberSprite(int number);
	CSprite* GetSpriteFromPosition(Vec2 position);
	void SetBorder(const Vec2& pos);
	Vec2 GetLastMousePos();
	void CompleteUpdate(char* fields);
	void ClearField(Vec2 position, bool isUndo = false);

	char* GetTempFieldBuffer();
	void TriggerUndo();
	
private:
	Undo undo;
	Border border;
	CDIB framebuffer;
	CSprite sudokuBackground;

	const Vec2 tileDimension = Vec2(50, 47);
	const Vec2 offsets = Vec2(5, 10);
	CSpriteList spriteList;
	std::vector<SpriteData> spriteMap;
	std::vector<char> tempFieldBuffer;

	Vec2 lastMousePos = Vec2(0, 0);
	const int WIDTH = 9;
	const int HEIGHT = 9;
};

