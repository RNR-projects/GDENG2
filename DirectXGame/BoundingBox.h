#pragma once
#include "GameObjectConstants.h"

class BoundingBox
{
public:
	BoundingBox(Vector3D pos, Vector3D rotation, float width, float height, float depth);
	~BoundingBox();

	void setPosition(Vector3D newPos);
	void setDimensions(float newWidth, float newHeight, float newDepth);
	void setRotation(Vector3D newRotation);

	bool checkRaycast(Vector3D rayOrigin, Vector3D rayDirection);

private:
	void updateEdges();

	Vector3D position;
	Vector3D scale;
	Vector3D rotation;

	float width;
	float height;
	float depth;

	Vector3D facePoints[6];
};

