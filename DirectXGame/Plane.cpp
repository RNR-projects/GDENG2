#include "Plane.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "IndexBuffer.h"
#include "RenderSystem.h"

/*Plane::Plane(std::string name, Vector3D pos, Vector3D scale, Vector3D color, Vector3D rot) : AGameObject(name)
{
	this->localPosition = pos;
	this->localScale = scale;
	this->colors = color;
	this->localRotation = rot;

	edges[0] = Vector3D(-this->localScale.x / 2.0f, 0.1f, -this->localScale.z / 2.0f);
	edges[1] = Vector3D(-this->localScale.x / 2.0f, 0.2f, this->localScale.z / 2.0f);
	edges[2] = Vector3D(this->localScale.x / 2.0f, 0.1f, -this->localScale.z / 2.0f);
	edges[3] = Vector3D(this->localScale.x / 2.0f, 0.2f, this->localScale.z / 2.0f);

	RenderSystem* graphEngine = GraphicsEngine::getInstance()->getRenderSystem();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	vertex list[] = {
		{ edges[0] + this->localPosition,		this->colors },
		{ edges[1] + this->localPosition,		this->colors },
		{ edges[2] + this->localPosition,		this->colors },
		{ edges[3] + this->localPosition,		this->colors }
	};

	unsigned int index_list[] = {
		0,1,2,
		1,2,3
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

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}


void Plane::setScale(float x, float y, float z)
{
	edges[0] = Vector3D(-x / 2.0f, 0.1f, -z / 2.0f);
	edges[1] = Vector3D(-x / 2.0f, 0.1f, z / 2.0f);
	edges[2] = Vector3D(x / 2.0f, 0.1f, -z / 2.0f);
	edges[3] = Vector3D(x / 2.0f, 0.1f, z / 2.0f);

	AGameObject::setScale(x, y, z);
}

void Plane::setScale(Vector3D scale)
{
	edges[0] = Vector3D(-scale.x / 2.0f, 0.1f, -scale.z / 2.0f);
	edges[1] = Vector3D(-scale.x / 2.0f, 0.1f, scale.z / 2.0f);
	edges[2] = Vector3D(scale.x / 2.0f, 0.1f, -scale.z / 2.0f);
	edges[3] = Vector3D(scale.x / 2.0f, 0.1f, scale.z / 2.0f);

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

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	Vector3D* worldLocations = getVertexWorldPositions();

	vertex list[] = {
		{ worldLocations[0],		this->colors },
		{ worldLocations[1],		this->colors },
		{ worldLocations[2],		this->colors },
		{ worldLocations[3],		this->colors }
	};

	UINT size_list = ARRAYSIZE(list);

	delete m_vb;
	m_vb = graphEngine->createVertexBuffer(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->getRenderSystem()->releaseCompiledShader();
}*/
