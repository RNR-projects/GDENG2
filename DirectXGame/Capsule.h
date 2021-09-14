#pragma once
#include "AGameObject.h"
class Capsule : public AGameObject
{
public:
	Capsule(std::string name, Vector3D pos, float radius, float cylinderHeight);
	~Capsule();

	virtual void update(float deltaTime) override;
	virtual void draw(ConstantBuffer* cb) override;

	void setRadius(float newRadius);
	void setCylinderHeight(float newHeight);

	float getRadius();
	float getCylinderHeight();

	std::vector<Vector3D> getVertexWorldPositions();

private:
	virtual void updateVertexLocations() override;

	void generateEdges();

	std::vector<Vector3D> edges;
	std::vector<Vector2D> texCoords;
	float radius;
	float cylinderHeight;

	class VertexBuffer* m_vb;
	class VertexShader* m_vs;
	class PixelShader* m_ps;
	class IndexBuffer* m_ib;

	class Texture* m_wood_tex;

};

