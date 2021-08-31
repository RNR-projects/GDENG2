#pragma once
#include "AGameObject.h"
class Plane : public AGameObject
{
public:
	Plane(std::string name, Vector3D pos, Vector3D scale, Vector3D color, Vector3D rot);
	~Plane();

	void setColors(Vector3D color);
	virtual void update(float deltaTime) override;
	virtual void draw(ConstantBuffer* cb) override;

	virtual void setScale(float x, float y, float z) override;
	virtual void setScale(Vector3D scale) override;

	Vector3D* getVertexWorldPositions();

private:
	virtual void updateVertexLocations() override;

	Vector3D colors;

	Vector3D edges[4];

	class VertexBuffer* m_vb;
	class VertexShader* m_vs;
	class PixelShader* m_ps;
	class IndexBuffer* m_ib;

	class Texture* tex;
};

