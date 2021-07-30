#pragma once
#include <math.h>

class Vector3D 
{
public:
	Vector3D(): x(0), y(0), z(0)
	{

	}
	
	Vector3D(float x, float y, float z): x(x), y(y), z(z)
	{

	}

	Vector3D(const Vector3D& vector): x(vector.x), y(vector.y), z(vector.z) 
	{

	}

	static Vector3D lerp(const Vector3D& start, const Vector3D& end, float delta)
	{
		Vector3D v;
		v.x = start.x * (1.0f - delta) + end.x * (delta);
		v.y = start.y * (1.0f - delta) + end.y * (delta);
		v.z = start.z * (1.0f - delta) + end.z * (delta);

		return v;
	}

	Vector3D operator +(const Vector3D& vector3)
	{
		Vector3D v;
		v.x = x + vector3.x;
		v.y = y + vector3.y;
		v.z = z + vector3.z;

		return v;
	}
	Vector3D operator -(const Vector3D& vector3)
	{
		Vector3D v;
		v.x = x - vector3.x;
		v.y = y - vector3.y;
		v.z = z - vector3.z;

		return v;
	}
	//Beware it uses sqrt which is expensive
	float getMagnitude()
	{
		return sqrtf(x * x + y * y + z * z);
	}

	void normalize()
	{
		float magnitude = getMagnitude();

		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
	}

	static float dotProduct(const Vector3D& vec1, const Vector3D& vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	}

	~Vector3D() 
	{

	}

	float x, y, z;
};