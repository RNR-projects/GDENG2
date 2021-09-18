#include "Plane.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "IndexBuffer.h"
#include "RenderSystem.h"
#include "PhysicsComponent.h"

Plane::Plane(std::string name, Vector3D pos, Vector3D scale, Vector3D color, Vector3D rot) : AGameObject(name, AGameObject::PrimitiveType::PLANE)
{
	this->localPosition = pos;
	this->localScale = scale;
	this->colors = color;
	this->localRotation = rot;
	this->localScale.y = 0.1f;

	edges[0] = Vector3D(-this->localScale.x / 2.0f, -0.05f, -this->localScale.z / 2.0f);
	edges[1] = Vector3D(-this->localScale.x / 2.0f, 0.05f, this->localScale.z / 2.0f);
	edges[2] = Vector3D(this->localScale.x / 2.0f, -0.05f, -this->localScale.z / 2.0f);
	edges[3] = Vector3D(this->localScale.x / 2.0f, 0.05f, this->localScale.z / 2.0f);

	RenderSystem* graphEngine = GraphicsEngine::getInstance()->getRenderSystem();
	
	tex = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\blank.jpg");

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	vertex list[] = {
		{ edges[0] + this->localPosition, Vector2D(0,0) },
		{ edges[1] + this->localPosition, Vector2D(0,1) },
		{ edges[2] + this->localPosition, Vector2D(1,0) },
		{ edges[3] + this->localPosition, Vector2D(1,1) }
	};

	unsigned int index_list[] = {
		0,1,2,
		1,3,2
	};

	UINT size_index_list = ARRAYSIZE(index_list);
	m_ib = graphEngine->createIndexBuffer(index_list, size_index_list);

	UINT size_list = ARRAYSIZE(list);

	m_vs = graphEngine->createVertexShader(shader_byte_code, size_shader);

	m_vb = graphEngine->createVertexBuffer(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	graphEngine->releaseCompiledShader();

	graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = graphEngine->createPixelShader(shader_byte_code, size_shader);

	graphEngine->releaseCompiledShader();
}

Plane::~Plane()
{
	delete tex;

	delete m_vb;
	delete m_vs;
	delete m_ps;
	delete m_ib;
}

void Plane::setColors(Vector3D color)
{
	this->colors = color;
}

void Plane::update(float deltaTime)
{
}

void Plane::draw(ConstantBuffer* cb)
{
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, cb);
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, cb);

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setTexture(m_ps, tex);

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}


void Plane::setScale(float x, float y, float z)
{
	edges[0] = Vector3D(-x / 2.0f, -0.05f, -z / 2.0f);
	edges[1] = Vector3D(-x / 2.0f, 0.05f, z / 2.0f);
	edges[2] = Vector3D(x / 2.0f, -0.05f, -z / 2.0f);
	edges[3] = Vector3D(x / 2.0f, 0.05f, z / 2.0f);
	this->localScale.y = 0.1f;

	AGameObject::setScale(x, y, z);
}

void Plane::setScale(Vector3D scale)
{
	edges[0] = Vector3D(-scale.x / 2.0f, -0.05f, -scale.z / 2.0f);
	edges[1] = Vector3D(-scale.x / 2.0f, 0.05f, scale.z / 2.0f);
	edges[2] = Vector3D(scale.x / 2.0f, -0.05f, -scale.z / 2.0f);
	edges[3] = Vector3D(scale.x / 2.0f, 0.05f, scale.z / 2.0f);
	this->localScale.y = 0.1f;

	AGameObject::setScale(scale);
}

Vector3D* Plane::getVertexWorldPositions()
{
	Vector3D worldLocations[] = {
		Quaternion::rotatePointEuler(edges[0], this->localRotation) + this->localPosition,
		Quaternion::rotatePointEuler(edges[1], this->localRotation) + this->localPosition,
		Quaternion::rotatePointEuler(edges[2], this->localRotation) + this->localPosition,
		Quaternion::rotatePointEuler(edges[3], this->localRotation) + this->localPosition
	};

	return worldLocations;
}

void Plane::updateVertexLocations()
{
	RenderSystem* graphEngine = GraphicsEngine::getInstance()->getRenderSystem();

	Vector3D* worldLocations = getVertexWorldPositions();

	vertex list[] = {
		{ worldLocations[0], Vector2D(0,0) },
		{ worldLocations[1], Vector2D(0,1) },
		{ worldLocations[2], Vector2D(1,0) },
		{ worldLocations[3], Vector2D(1,1) }
	};

	UINT size_list = ARRAYSIZE(list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::getInstance()->getVertexMeshLayoutShaderByteCodeAndSize(&shader_byte_code, &size_shader);
	delete m_vb;
	m_vb = graphEngine->createVertexBuffer(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
}
