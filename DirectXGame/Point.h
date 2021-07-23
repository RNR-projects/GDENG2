#pragma once

class Point
{
public:
	Point() : x(0), y(0)
	{

	}

	Point(float x, float y) : x(x), y(y)
	{

	}

	Point(const Point& point) : x(point.x), y(point.y)
	{

	}

	~Point()
	{

	}

	float x = 0;
	float y = 0;
};