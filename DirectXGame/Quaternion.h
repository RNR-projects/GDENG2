#pragma once
#include <memory>
#include "Vector3D.h"

class Quaternion
{
public:
	Quaternion() : q(0), i(0), j(0), k(0)
	{

	}

	Quaternion(float q, float i, float j, float k) : q(q), i(i), j(j), k(k)
	{

	}

	Quaternion(const Quaternion& quaternion) : q(quaternion.q), i(quaternion.i), j(quaternion.j), k(quaternion.k)
	{

	}

	static Quaternion eulerToQuaternion(const Vector3D& vector)
	{
		Quaternion quaternion;
		quaternion.q = cos(vector.x / 2.0f) * cos(vector.y / 2.0f) * cos(vector.z / 2.0f) + sin(vector.x / 2.0f) * sin(vector.y / 2.0f) * sin(vector.z / 2.0f);
		quaternion.i = sin(vector.x / 2.0f) * cos(vector.y / 2.0f) * cos(vector.z / 2.0f) - cos(vector.x / 2.0f) * sin(vector.y / 2.0f) * sin(vector.z / 2.0f);
		quaternion.j = cos(vector.x / 2.0f) * sin(vector.y / 2.0f) * cos(vector.z / 2.0f) + sin(vector.x / 2.0f) * cos(vector.y / 2.0f) * sin(vector.z / 2.0f);
		quaternion.k = cos(vector.x / 2.0f) * cos(vector.y / 2.0f) * sin(vector.z / 2.0f) - sin(vector.x / 2.0f) * sin(vector.y / 2.0f) * cos(vector.z / 2.0f);

		return quaternion;
	}

	static Vector3D toEuler(const Quaternion& quaterion)
	{
		Vector3D v;
		v.x = atan2f(2.0f * (quaterion.q * quaterion.i + quaterion.j * quaterion.k), 
			quaterion.q * quaterion.q - quaterion.i * quaterion.i - quaterion.j * quaterion.j + quaterion.k * quaterion.k);
		v.y = asinf(2.0f * (quaterion.q * quaterion.j - quaterion.i * quaterion.k));
		v.z = atan2f(2.0f * (quaterion.q * quaterion.k + quaterion.i * quaterion.j), 
			quaterion.q * quaterion.q + quaterion.i * quaterion.i - quaterion.j * quaterion.j - quaterion.k * quaterion.k);

		return v;
	}

	Quaternion operator *(const Quaternion& quaternion)
	{
		Quaternion result;
		result.q = q * quaternion.q - i * quaternion.i - j * quaternion.j - k * quaternion.k;
		result.i = q * quaternion.i + i * quaternion.q - j * quaternion.k + k * quaternion.j;
		result.j = q * quaternion.j + i * quaternion.k + j * quaternion.q - k * quaternion.i;
		result.k = q * quaternion.k - i * quaternion.j + j * quaternion.i + k * quaternion.q;

		return result;
	}

	void invert()
	{
		i *= -1;
		j *= -1;
		k *= -1;
	}

	//Quaternion rotation
	static Vector3D rotatePointQuaternion(const Vector3D& point, const Quaternion& rotation)
	{
		Quaternion pointQuaternion(0, point.x, point.y, point.z);
		Quaternion inverse(rotation);
		Quaternion rot(rotation);
		Quaternion result;

		inverse.invert();

		result = rot * pointQuaternion * inverse;

		return Vector3D(result.i, result.j, result.k);	
	}
	
	//Euler angles rotation
	static Vector3D rotatePointEuler(const Vector3D& point, const Vector3D& rotation)
	{
		Vector3D rot(rotation);
		Quaternion quatRotation(eulerToQuaternion(rot));
		Quaternion pointQuaternion(0, point.x, point.y, point.z);
		Quaternion inverse(quatRotation);
		Quaternion result;

		inverse.invert();

		result = quatRotation * pointQuaternion * inverse;

		return Vector3D(result.i, result.j, result.k);	
	}

	~Quaternion()
	{

	}

	float q, i, j, k;
};