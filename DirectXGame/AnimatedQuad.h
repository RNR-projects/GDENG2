#pragma once
#include "GameObjectConstants.h"
class AnimatedQuad
{
public:
	AnimatedQuad();
	~AnimatedQuad();

	void draw(class ConstantBuffer* cb, float deltaTime);

	void createQuad(Vector3D edge[4], Vector3D edge2[4], Vector3D colors[4], Vector3D colors2[4]);

private:
	void updateVertexLocations();

	float deltaTime = 0.0f;
	float totalElapsedTime = 0.0f;
	float speed = 1.0f;

	Vector3D colors[4];
	Vector3D colors2[4];

	Vector3D edges[4];
	Vector3D edges2[4];

	class VertexBuffer* m_vb;
	class VertexShader* m_vs;
	class PixelShader* m_ps;
	class IndexBuffer* m_ib;
};

