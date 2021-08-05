#include "Cube.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "IndexBuffer.h"
#include "BoundingBox.h"
#include <random>

Cube::Cube(std::string name, Vector3D pos, Vector3D scale, Vector3D color, Vector3D rot) : AGameObject(name)
{
	this->localPosition = pos;
	this->localScale = scale;
	this->colors = color;
	this->localRotation = rot;
	this->speed = rand() % 100 / 100.0f + 0.5f;
	this->colors2[0] = Vector3D(1, 0, 1);
	this->colors2[1] = Vector3D(1, 1, 0);
	this->colors2[2] = Vector3D(0, 1, 1);
	this->colors2[3] = Vector3D(0, 0, 1);
	this->colors2[4] = Vector3D(0, 1, 0);
	this->colors2[5] = Vector3D(1, 0, 0);
	this->colors2[6] = Vector3D(1, 1, 1);
	this->colors2[7] = Vector3D(0, 0, 0);

	edges[0] = Vector3D(-this->localScale.x / 2.0f, -this->localScale.y / 2.0f, -this->localScale.z / 2.0f);
	edges[1] = Vector3D(-this->localScale.x / 2.0f, this->localScale.y / 2.0f, -this->localScale.z / 2.0f);
	edges[2] = Vector3D(this->localScale.x / 2.0f, this->localScale.y / 2.0f, -this->localScale.z / 2.0f);
	edges[3] = Vector3D(this->localScale.x / 2.0f, -this->localScale.y / 2.0f, -this->localScale.z / 2.0f);
	edges[4] = Vector3D(this->localScale.x / 2.0f, -this->localScale.y / 2.0f, this->localScale.z / 2.0f);
	edges[5] = Vector3D(this->localScale.x / 2.0f, this->localScale.y / 2.0f, this->localScale.z / 2.0f);
	edges[6] = Vector3D(-this->localScale.x / 2.0f, this->localScale.y / 2.0f, this->localScale.z / 2.0f);
	edges[7] = Vector3D(-this->localScale.x / 2.0f, -this->localScale.y / 2.0f, this->localScale.z / 2.0f);

	collisionBox = new BoundingBox(this->localPosition, this->localRotation, 1.0f * this->localScale.x, 1.0f * this->localScale.y, 1.0f * this->localScale.z);

	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);


	vertex list[] = {
		{ edges[0] + this->localPosition,		this->colors2[0] },
		{ edges[1] + this->localPosition,		this->colors2[1] },
		{ edges[2] + this->localPosition,		this->colors2[2] },
		{ edges[3] + this->localPosition,		this->colors2[3] },

		{ edges[4] + this->localPosition,		this->colors2[4] },
		{ edges[5] + this->localPosition,		this->colors2[5] },
		{ edges[6] + this->localPosition,		this->colors2[6] },
		{ edges[7] + this->localPosition,		this->colors2[7] },
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

Cube::~Cube()
{
	delete collisionBox;

	m_vb->release();
	m_vs->release();
	m_ps->release();
	m_ib->release();
}

void Cube::setPosition(float x, float y, float z)
{
	AGameObject::setPosition(x, y, z);
	collisionBox->setPosition(this->localPosition);
}

void Cube::setPosition(Vector3D pos)
{
	AGameObject::setPosition(pos);
	collisionBox->setPosition(this->localPosition);
}

void Cube::setScale(float x, float y, float z)
{
	edges[0] = Vector3D(-x / 2.0f, -y / 2.0f, -z / 2.0f);
	edges[1] = Vector3D(-x / 2.0f, y / 2.0f, -z / 2.0f);
	edges[2] = Vector3D(x / 2.0f, y / 2.0f, -z / 2.0f);
	edges[3] = Vector3D(x / 2.0f, -y / 2.0f, -z / 2.0f);
	edges[4] = Vector3D(x / 2.0f, -y / 2.0f, z / 2.0f);
	edges[5] = Vector3D(x / 2.0f, y / 2.0f, z / 2.0f);
	edges[6] = Vector3D(-x / 2.0f, y / 2.0f, z / 2.0f);
	edges[7] = Vector3D(-x / 2.0f, -y / 2.0f, z / 2.0f);

	AGameObject::setScale(x, y, z);
	collisionBox->setDimensions(1.0f * this->localScale.x, 1.0f * this->localScale.y, 1.0f * this->localScale.z);
}

void Cube::setScale(Vector3D newScale)
{
	edges[0] = Vector3D(-newScale.x / 2.0f, -newScale.y / 2.0f, -newScale.z / 2.0f);
	edges[1] = Vector3D(-newScale.x / 2.0f, newScale.y / 2.0f, -newScale.z / 2.0f);
	edges[2] = Vector3D(newScale.x / 2.0f, newScale.y / 2.0f, -newScale.z / 2.0f);
	edges[3] = Vector3D(newScale.x / 2.0f, -newScale.y / 2.0f, -newScale.z / 2.0f);
	edges[4] = Vector3D(newScale.x / 2.0f, -newScale.y / 2.0f, newScale.z / 2.0f);
	edges[5] = Vector3D(newScale.x / 2.0f, newScale.y / 2.0f, newScale.z / 2.0f);
	edges[6] = Vector3D(-newScale.x / 2.0f, newScale.y / 2.0f, newScale.z / 2.0f);
	edges[7] = Vector3D(-newScale.x / 2.0f, -newScale.y / 2.0f, newScale.z / 2.0f);

	AGameObject::setScale(newScale);
	collisionBox->setDimensions(1.0f * this->localScale.x, 1.0f * this->localScale.y, 1.0f * this->localScale.z);
}

void Cube::setColors(Vector3D color)
{
	this->colors = color;

	updateVertexLocations();
}

void Cube::setRotation(float x, float y, float z)
{
	AGameObject::setRotation(x, y, z);
	collisionBox->setRotation(Vector3D(x, y, z));
}

void Cube::setRotation(Vector3D rotation)
{
	AGameObject::setRotation(rotation);
	collisionBox->setRotation(rotation);
}

void Cube::update(float deltaTime)
{
	//rot_x += deltaTime * speed;

	//rot_y += deltaTime * speed;

	//rot_z += deltaTime * speed;

	this->setRotation(rot_x, rot_y, rot_z);
}

void Cube::draw(ConstantBuffer* cb)
{
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, cb);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

Vector3D* Cube::getVertexWorldPositions()
{
	Vector3D worldLocations[] = {
		Quaternion::rotatePointEuler(edges[0], this->localRotation) + this->localPosition,
		Quaternion::rotatePointEuler(edges[1], this->localRotation) + this->localPosition,
		Quaternion::rotatePointEuler(edges[2], this->localRotation) + this->localPosition,
		Quaternion::rotatePointEuler(edges[3], this->localRotation) + this->localPosition,
		Quaternion::rotatePointEuler(edges[4], this->localRotation) + this->localPosition,
		Quaternion::rotatePointEuler(edges[5], this->localRotation) + this->localPosition,
		Quaternion::rotatePointEuler(edges[6], this->localRotation) + this->localPosition,
		Quaternion::rotatePointEuler(edges[7], this->localRotation) + this->localPosition,
	};

	return worldLocations;
}

bool Cube::checkRaycast(Vector3D rayOrigin, Vector3D rayDirection)
{
	return collisionBox->checkRaycast(rayOrigin, rayDirection);
}

void Cube::updateVertexLocations()
{
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	Vector3D* worldLocations = getVertexWorldPositions();

	vertex list[] = {
		{ worldLocations[0],		this->colors2[0] },
		{ worldLocations[1],		this->colors2[1] },
		{ worldLocations[2],		this->colors2[2] },
		{ worldLocations[3],		this->colors2[3] },

		{ worldLocations[4],		this->colors2[4] },
		{ worldLocations[5],		this->colors2[5] },
		{ worldLocations[6],		this->colors2[6] },
		{ worldLocations[7],		this->colors2[7] },
	};

	UINT size_list = ARRAYSIZE(list);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->releaseCompiledShader();
}
