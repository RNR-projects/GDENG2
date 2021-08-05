#include "Plane.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "IndexBuffer.h"

Plane::Plane(std::string name, Vector3D pos, Vector3D scale, Vector3D color, Vector3D rot) : AGameObject(name)
{
	this->localPosition = pos;
	this->localScale = scale;
	this->colors = color;
	this->localRotation = rot;

	edges[0] = Vector3D(-this->localScale.x / 2.0f, 0.1f, -this->localScale.z / 2.0f);
	edges[1] = Vector3D(-this->localScale.x / 2.0f, 0.2f, this->localScale.z / 2.0f);
	edges[2] = Vector3D(this->localScale.x / 2.0f, 0.1f, -this->localScale.z / 2.0f);
	edges[3] = Vector3D(this->localScale.x / 2.0f, 0.2f, this->localScale.z / 2.0f);

	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

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

	m_ib = GraphicsEngine::getInstance()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib->load(index_list, size_index_list);

	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();

	UINT size_list = ARRAYSIZE(list);

	m_vs = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->releaseCompiledShader();

	GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->releaseCompiledShader();
}

Plane::~Plane()
{
	m_vb->release();
	m_vs->release();
	m_ps->release();
	m_ib->release();
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
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, cb);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
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
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

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

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->releaseCompiledShader();
}
