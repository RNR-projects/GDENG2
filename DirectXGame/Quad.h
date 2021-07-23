#pragma once
#include "GameObjectConstants.h"

class Quad
{
public:
	Quad();
	~Quad();

	void draw(class ConstantBuffer* cb);

	void createQuad(Vector3D pos, Vector3D scale, Vector3D color);
	void setPosition(Vector3D newPos);
	void setScale(Vector3D newScale);
	void setColors(Vector3D color);
	void setRotation(Vector3D rotation);

	Vector3D* getVertexWorldPositions();

	bool checkRaycast(Vector3D rayOrigin, Vector3D rayDirection);

private:
	void updateVertexLocations();

	Vector3D position;
	Vector3D scale;
	Vector3D colors;
	Vector3D rotation;

	Vector3D edges[8];

	class VertexBuffer* m_vb;
	class VertexShader* m_vs;
	class PixelShader* m_ps;
	class IndexBuffer* m_ib;

	class BoundingSphere* collisionSphere;
};

