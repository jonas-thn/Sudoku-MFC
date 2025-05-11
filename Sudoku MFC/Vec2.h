#pragma once
struct Vec2
{
	static Vec2 Zero() { return Vec2(0, 0); }

	Vec2() : x(0), y(0) {}
	Vec2(int x, int y) : x(x), y(y) {}
	Vec2(const Vec2& other) : x(other.x), y(other.y) {}

	int x;
	int y;

	Vec2 operator+(const Vec2& other) const
	{
		return Vec2(x + other.x, y + other.y);
	}

	Vec2 operator-(const Vec2& other) const
	{
		return Vec2(x - other.x, y - other.y);
	}

	bool operator==(const Vec2& other) const
	{
		return (x == other.x && y == other.y);
	}
};

