#pragma once
#include "AGameObject.h"

class LoadedMeshObject : public AGameObject
{
public:
	LoadedMeshObject(std::string name, Vector3D pos, Vector3D scale, Vector3D rot, const wchar_t* objPath);
	~LoadedMeshObject();

	virtual void update(float deltaTime) override;
	virtual void draw(ConstantBuffer* cb) override;

	virtual void setPosition(float x, float y, float z) override;
	virtual void setPosition(Vector3D pos) override;

	virtual void setScale(float x, float y, float z) override;
	virtual void setScale(Vector3D scale) override;

	virtual void setRotation(float x, float y, float z) override;
	virtual void setRotation(Vector3D rot) override;

private:
	virtual void updateVertexLocations() override;

	class VertexBuffer* m_vb;
	class VertexShader* m_vs;
	class PixelShader* m_ps;
	class IndexBuffer* m_ib;

	class Texture* m_wood_tex;

	class Mesh* m_mesh;
};

