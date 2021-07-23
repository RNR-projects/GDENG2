#include "Quad.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "IndexBuffer.h"
#include "BoundingSphere.h"

Quad::Quad()
{
	rotation = Vector3D();
	edges[0] = Vector3D(-0.5f, -0.5f, -0.5f);
	edges[1] = Vector3D(-0.5f, 0.5f, -0.5f);
	edges[2] = Vector3D(0.5f, 0.5f, -0.5f);
	edges[3] = Vector3D(0.5f, -0.5f, -0.5f);
	edges[4] = Vector3D(0.5f, -0.5f, 0.5f);
	edges[5] = Vector3D(0.5f, 0.5f, 0.5f);
	edges[6] = Vector3D(-0.5f, 0.5f, 0.5f);
	edges[7] = Vector3D(-0.5f, -0.5f, 0.5f);
}

Quad::~Quad()
{
	delete collisionSphere;

	m_vb->release();
	m_vs->release();
	m_ps->release();
	m_ib->release();
}

void Quad::draw(ConstantBuffer* cb)
{
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, cb);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Quad::createQuad(Vector3D pos, Vector3D scale, Vector3D color)
{
	this->position = pos;
	this->scale = scale;
	this->colors = color;

	collisionSphere = new BoundingSphere(this->position, 0.5f);

	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);


	vertex list[] = {
		/*{Vector3D(-0.5f, -0.5f, 0),	this->colors},
		{Vector3D(-0.5, 0.5f, 0),		this->colors},
		{Vector3D(0.5f, -0.5f, 0),	this->colors},
		{Vector3D(0.5f, 0.5f, 0),		this->colors}*/
		{ edges[0] + this->position,		this->colors },
		{ edges[1] + this->position,		this->colors },
		{ edges[2] + this->position,		this->colors },
		{ edges[3] + this->position,		this->colors },

		{ edges[4] + this->position,		this->colors },
		{ edges[5] + this->position,		this->colors },
		{ edges[6] + this->position,		this->colors },
		{ edges[7] + this->position,		this->colors },
	};

	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();

	UINT size_list = ARRAYSIZE(list);

	unsigned int index_list[] = {
		0,1,2,
		2,3,0,

		4,5,6,
		6,7,4,

		1,6,5,
		5,2,1,

		7,0,3,
		3,4,7,

		3,2,5,
		5,4,3,

		7,6,1,
		1,0,7
	};

	m_ib = GraphicsEngine::getInstance()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib->load(index_list, size_index_list);

	m_vs = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->releaseCompiledShader();

	GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->releaseCompiledShader();
}

void Quad::setPosition(Vector3D newPos)
{
	this->position = newPos;

	updateVertexLocations();
}

void Quad::setScale(Vector3D newScale)
{
	this->scale = newScale;

	updateVertexLocations();
}

void Quad::setColors(Vector3D color)
{
	this->colors = color;

	updateVertexLocations();
}

void Quad::setRotation(Vector3D rotation)
{
	this->rotation = rotation;

	updateVertexLocations();
}

Vector3D* Quad::getVertexWorldPositions()
{
	Vector3D worldLocations[] = {
		Quaternion::rotatePointEuler(edges[0], rotation) + this->position,
		Quaternion::rotatePointEuler(edges[1], rotation) + this->position,
		Quaternion::rotatePointEuler(edges[2], rotation) + this->position,
		Quaternion::rotatePointEuler(edges[3], rotation) + this->position,
		Quaternion::rotatePointEuler(edges[4], rotation) + this->position,
		Quaternion::rotatePointEuler(edges[5], rotation) + this->position,
		Quaternion::rotatePointEuler(edges[6], rotation) + this->position,
		Quaternion::rotatePointEuler(edges[7], rotation) + this->position,
	};

	return worldLocations;
}

bool Quad::checkRaycast(Vector3D rayOrigin, Vector3D rayDirection)
{
	return collisionSphere->checkRaycast(rayOrigin, rayDirection);
}

void Quad::updateVertexLocations()
{
	collisionSphere->setPosition(this->position);

	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	Vector3D* worldLocations = getVertexWorldPositions();

	vertex list[] = {
		{ worldLocations[0],		this->colors },
		{ worldLocations[1],		this->colors },
		{ worldLocations[2],		this->colors },
		{ worldLocations[3],		this->colors },

		{ worldLocations[4],		this->colors },
		{ worldLocations[5],		this->colors },
		{ worldLocations[6],		this->colors },
		{ worldLocations[7],		this->colors },
	};

	UINT size_list = ARRAYSIZE(list);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->releaseCompiledShader();
}
