#pragma once
#include "Vec2.h"

class Feld
{
public:
	Feld();
	~Feld();

	const int width = 40;
	const int height = 40;
private:
	Vec2 position;
	Vec2 coordinates;
	int number;
};

