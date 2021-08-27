#pragma once
#include "AGameObject.h"

class Cube : public AGameObject
{
public:
	Cube(std::string name, Vector3D pos, Vector3D scale, Vector3D color, Vector3D rot);
	~Cube();

	void setColors(Vector3D color);
	virtual void update(float deltaTime) override;
	virtual void draw(ConstantBuffer* cb) override;

	virtual void setPosition(float x, float y, float z) override;
	virtual void setPosition(Vector3D pos) override;

	virtual void setScale(float x, float y, float z) override;
	virtual void setScale(Vector3D scale) override;

	virtual void setRotation(float x, float y, float z) override;
	virtual void setRotation(Vector3D rot) override;

	Vector3D* getVertexWorldPositions();

	float checkRaycast(Vector3D rayOrigin, Vector3D rayDirection);

private:
	virtual void updateVertexLocations() override;

	Vector3D colors;
	Vector3D colors2[8];

	float rot_x = 0;
	float rot_y = 0;
	float speed = 1;

	Vector3D edges[8];

	class VertexBuffer* m_vb;
	class VertexShader* m_vs;
	class PixelShader* m_ps;
	class IndexBuffer* m_ib;

	class BoundingBox* collisionBox;

	class Texture* m_wood_tex;

	class Mesh* m_mesh;
};

