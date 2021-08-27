#pragma once
#include <math.h>

class Vector2D
{
public:
	Vector2D() : x(0), y(0)
	{

	}

	Vector2D(float x, float y) : x(x), y(y)
	{

	}

	Vector2D(const Vector2D& vector) : x(vector.x), y(vector.y)
	{

	}

	static Vector2D lerp(const Vector2D& start, const Vector2D& end, float delta)
	{
		Vector2D v;
		v.x = start.x * (1.0f - delta) + end.x * (delta);
		v.y = start.y * (1.0f - delta) + end.y * (delta);

		return v;
	}

	Vector2D operator +(const Vector2D& vector3)
	{
		Vector2D v;
		v.x = x + vector3.x;
		v.y = y + vector3.y;

		return v;
	}
	Vector2D operator -(const Vector2D& vector3)
	{
		Vector2D v;
		v.x = x - vector3.x;
		v.y = y - vector3.y;

		return v;
	}
	Vector2D operator *(const float& scalar)
	{
		Vector2D v;
		v.x = x * scalar;
		v.y = y * scalar;

		return v;
	}
	//Beware it uses sqrt which is expensive
	float getMagnitude()
	{
		return sqrtf(x * x + y * y);
	}

	void normalize()
	{
		float magnitude = getMagnitude();

		x /= magnitude;
		y /= magnitude;
	}

	static float dotProduct(const Vector2D& vec1, const Vector2D& vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}

	~Vector2D()
	{

	}

	float x, y;
};