#pragma once
#include "AGameObject.h"

class LoadedMeshObject : public AGameObject
{
public:
	LoadedMeshObject(std::string name, Vector3D pos, Vector3D scale, Vector3D rot);
	~LoadedMeshObject();

	virtual void update(float deltaTime) override;
	virtual void draw(ConstantBuffer* cb) override;

	Vector3D* getVertexWorldPositions();

private:
	virtual void updateVertexLocations() override;

	class VertexBuffer* m_vb;
	class VertexShader* m_vs;
	class PixelShader* m_ps;
	class IndexBuffer* m_ib;

	class Texture* m_wood_tex;

	class Mesh* m_mesh;
};

