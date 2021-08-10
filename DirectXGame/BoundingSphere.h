#pragma once
#include "GameObjectConstants.h"

class BoundingSphere
{
public:
	BoundingSphere(Vector3D pos, float radius);
	~BoundingSphere();

	void setPosition(Vector3D newPos);
	void setRadius(float newRadius);

	float checkRaycast(Vector3D rayOrigin, Vector3D rayDirection);

private:
	Vector3D position;
	Vector3D scale;

	float radius;
};

