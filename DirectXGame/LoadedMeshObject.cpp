#include "LoadedMeshObject.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "IndexBuffer.h"
#include "RenderSystem.h"
#include "Texture.h"
#include "Mesh.h"

LoadedMeshObject::LoadedMeshObject(std::string name, Vector3D pos, Vector3D scale, Vector3D rot, const wchar_t* objPath) : AGameObject(name)
{
	this->localPosition = pos;
	this->localScale = scale;
	this->localRotation = rot;

	m_wood_tex = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\brick.png");
	m_mesh = GraphicsEngine::getInstance()->getMeshManager()->creatMeshFromFile(objPath);

	RenderSystem* graphEngine = GraphicsEngine::getInstance()->getRenderSystem();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = graphEngine->createVertexShader(shader_byte_code, size_shader);

	graphEngine->releaseCompiledShader();

	graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = graphEngine->createPixelShader(shader_byte_code, size_shader);

	graphEngine->releaseCompiledShader();
}

LoadedMeshObject::~LoadedMeshObject()
{
	delete m_vb;
	delete m_vs;
	delete m_ps;
	delete m_ib;
}

void LoadedMeshObject::update(float deltaTime)
{
	
}

void LoadedMeshObject::draw(ConstantBuffer* cb)
{
	if (m_mesh != nullptr)
	{
		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, cb);
		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, cb);

		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setTexture(m_ps, m_wood_tex);

		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_mesh->getVertexBuffer());
		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_mesh->getIndexBuffer());

		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_mesh->getIndexBuffer()->getSizeIndexList(), 0, 0);
	}
}

void LoadedMeshObject::setPosition(float x, float y, float z)
{
	AGameObject::setPosition(x, y, z);
	m_mesh->moveVertexLocations(Vector3D(x, y, z));
}

void LoadedMeshObject::setPosition(Vector3D pos)
{
	AGameObject::setPosition(pos);
	m_mesh->moveVertexLocations(pos);
}

void LoadedMeshObject::setScale(float x, float y, float z)
{
	AGameObject::setScale(x, y, z);
	m_mesh->scaleVertexLocations(Vector3D(x, y, z));
}

void LoadedMeshObject::setScale(Vector3D scale)
{
	AGameObject::setScale(scale);
	m_mesh->scaleVertexLocations(scale);
}

void LoadedMeshObject::setRotation(float x, float y, float z)
{
	AGameObject::setRotation(x, y, z);
	m_mesh->rotateVertexLocations(Vector3D(x, y, z));
}

void LoadedMeshObject::setRotation(Vector3D rot)
{
	AGameObject::setRotation(rot);
	m_mesh->rotateVertexLocations(rot);
}

void LoadedMeshObject::updateVertexLocations()
{
	
}
