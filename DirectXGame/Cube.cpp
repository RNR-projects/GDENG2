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
#include "RenderSystem.h"
#include "Texture.h"
#include "PhysicsComponent.h"

Cube::Cube(std::string name, Vector3D pos, Vector3D scale, Vector3D color, Vector3D rot) : AGameObject(name, AGameObject::PrimitiveType::CUBE)
{
	this->localPosition = pos;
	this->localScale = scale;
	this->colors = color;
	this->localRotation = rot;
	this->speed = rand() % 100 / 100.0f + 0.5f;
	/*this->colors2[0] = Vector3D(1, 0, 1);
	this->colors2[1] = Vector3D(1, 1, 0);
	this->colors2[2] = Vector3D(0, 1, 1);
	this->colors2[3] = Vector3D(0, 0, 1);
	this->colors2[4] = Vector3D(0, 1, 0);
	this->colors2[5] = Vector3D(1, 0, 0);
	this->colors2[6] = Vector3D(1, 1, 1);
	this->colors2[7] = Vector3D(0, 0, 0);*/

	m_wood_tex = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\brick.png");

	edges[0] = Vector3D(-this->localScale.x / 2.0f, -this->localScale.y / 2.0f, -this->localScale.z / 2.0f);
	edges[1] = Vector3D(-this->localScale.x / 2.0f, this->localScale.y / 2.0f, -this->localScale.z / 2.0f);
	edges[2] = Vector3D(this->localScale.x / 2.0f, this->localScale.y / 2.0f, -this->localScale.z / 2.0f);
	edges[3] = Vector3D(this->localScale.x / 2.0f, -this->localScale.y / 2.0f, -this->localScale.z / 2.0f);
	edges[4] = Vector3D(this->localScale.x / 2.0f, -this->localScale.y / 2.0f, this->localScale.z / 2.0f);
	edges[5] = Vector3D(this->localScale.x / 2.0f, this->localScale.y / 2.0f, this->localScale.z / 2.0f);
	edges[6] = Vector3D(-this->localScale.x / 2.0f, this->localScale.y / 2.0f, this->localScale.z / 2.0f);
	edges[7] = Vector3D(-this->localScale.x / 2.0f, -this->localScale.y / 2.0f, this->localScale.z / 2.0f);

	collisionBox = new BoundingBox(this->localPosition, this->localRotation, 1.0f * this->localScale.x, 1.0f * this->localScale.y, 1.0f * this->localScale.z);

	RenderSystem* graphEngine = GraphicsEngine::getInstance()->getRenderSystem();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	Vector3D* worldLocations = getVertexWorldPositions();

	Vector3D positionList[] = {
		worldLocations[0],
		worldLocations[1],
		worldLocations[2],
		worldLocations[3],

		worldLocations[4],
		worldLocations[5],
		worldLocations[6],
		worldLocations[7],
	};

	Vector2D texcoordList[] = {
		/*{worldLocations[0],	this->colors},
		{ worldLocations[1],	this->colors },
		{ worldLocations[2],	this->colors },
		{ worldLocations[3],	this->colors },

		{ worldLocations[4],	this->colors },
		{ worldLocations[5],	this->colors },
		{ worldLocations[6],	this->colors },
		{ worldLocations[7],	this->colors },*/
		Vector2D(0,0),
		Vector2D(0,1),
		Vector2D(1,0),
		Vector2D(1,1)
	};

	vertex vertexList[] = {
		{ positionList[0],texcoordList[1] },
		{ positionList[1],texcoordList[0] },
		{ positionList[2],texcoordList[2] },
		{ positionList[3],texcoordList[3] },


		{ positionList[4],texcoordList[1] },
		{ positionList[5],texcoordList[0] },
		{ positionList[6],texcoordList[2] },
		{ positionList[7],texcoordList[3] },


		{ positionList[1],texcoordList[1] },
		{ positionList[6],texcoordList[0] },
		{ positionList[5],texcoordList[2] },
		{ positionList[2],texcoordList[3] },

		{ positionList[7],texcoordList[1] },
		{ positionList[0],texcoordList[0] },
		{ positionList[3],texcoordList[2] },
		{ positionList[4],texcoordList[3] },

		{ positionList[3],texcoordList[1] },
		{ positionList[2],texcoordList[0] },
		{ positionList[5],texcoordList[2] },
		{ positionList[4],texcoordList[3] },

		{ positionList[7],texcoordList[1] },
		{ positionList[6],texcoordList[0] },
		{ positionList[1],texcoordList[2] },
		{ positionList[0],texcoordList[3] }
	};

	UINT size_list = ARRAYSIZE(vertexList);

	unsigned int index_list[] = {
		0,1,2,  
		2,3,0,  
		
		4,5,6,
		6,7,4,
		
		8,9,10,
		10,11,8,
		
		12,13,14,
		14,15,12,
		
		16,17,18,
		18,19,16,
		
		20,21,22,
		22,23,20
	};

	UINT size_index_list = ARRAYSIZE(index_list);
	m_ib = graphEngine->createIndexBuffer(index_list, size_index_list);

	m_vs = graphEngine->createVertexShader(shader_byte_code, size_shader);

	m_vb = graphEngine->createVertexBuffer(vertexList, sizeof(vertex), size_list, shader_byte_code, size_shader);

	graphEngine->releaseCompiledShader();

	graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = graphEngine->createPixelShader(shader_byte_code, size_shader);

	graphEngine->releaseCompiledShader();
}

Cube::~Cube()
{
	delete collisionBox;

	delete m_vb;
	delete m_vs;
	delete m_ps;
	delete m_ib;
}

void Cube::setPosition(float x, float y, float z)
{
	AGameObject::setPosition(x, y, z);
	//collisionBox->setPosition(this->localPosition);
}

void Cube::setPosition(Vector3D pos)
{
	AGameObject::setPosition(pos);
	//collisionBox->setPosition(this->localPosition);
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
	//collisionBox->setDimensions(1.0f * this->localScale.x, 1.0f * this->localScale.y, 1.0f * this->localScale.z);
}

void Cube::setColors(Vector3D color)
{
	this->colors = color;

	updateVertexLocations();
}

void Cube::setRotation(float x, float y, float z)
{
	AGameObject::setRotation(x, y, z);
	//collisionBox->setRotation(Vector3D(x, y, z));
}

void Cube::setRotation(Vector3D rotation)
{
	AGameObject::setRotation(rotation);
	//collisionBox->setRotation(rotation);
}

void Cube::update(float deltaTime)
{
	//rot_x += deltaTime * speed;

	//rot_y += deltaTime * speed;

	//this->setRotation(rot_x, rot_y, 0);
}

void Cube::draw(ConstantBuffer* cb)
{
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, cb);
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, cb);

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);
	
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setTexture(m_ps, m_wood_tex);

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
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

float Cube::checkRaycast(Vector3D rayOrigin, Vector3D rayDirection)
{
	return collisionBox->checkRaycast(rayOrigin, rayDirection);
}

void Cube::updateVertexLocations()
{
	RenderSystem* graphEngine = GraphicsEngine::getInstance()->getRenderSystem();

	Vector3D* worldLocations = getVertexWorldPositions();

	Vector3D positionList[] = {
		worldLocations[0],
		worldLocations[1],
		worldLocations[2],
		worldLocations[3],

		worldLocations[4],
		worldLocations[5],
		worldLocations[6],
		worldLocations[7],
	};

	Vector2D texcoordList[] = {
		Vector2D(0,0),
		Vector2D(0,1),
		Vector2D(1,0),
		Vector2D(1,1)
	};

	vertex vertexList[] = {
		{ positionList[0],texcoordList[1] },
		{ positionList[1],texcoordList[0] },
		{ positionList[2],texcoordList[2] },
		{ positionList[3],texcoordList[3] },


		{ positionList[4],texcoordList[1] },
		{ positionList[5],texcoordList[0] },
		{ positionList[6],texcoordList[2] },
		{ positionList[7],texcoordList[3] },


		{ positionList[1],texcoordList[1] },
		{ positionList[6],texcoordList[0] },
		{ positionList[5],texcoordList[2] },
		{ positionList[2],texcoordList[3] },

		{ positionList[7],texcoordList[1] },
		{ positionList[0],texcoordList[0] },
		{ positionList[3],texcoordList[2] },
		{ positionList[4],texcoordList[3] },

		{ positionList[3],texcoordList[1] },
		{ positionList[2],texcoordList[0] },
		{ positionList[5],texcoordList[2] },
		{ positionList[4],texcoordList[3] },

		{ positionList[7],texcoordList[1] },
		{ positionList[6],texcoordList[0] },
		{ positionList[1],texcoordList[2] },
		{ positionList[0],texcoordList[3] }
	};

	UINT size_list = ARRAYSIZE(vertexList);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::getInstance()->getVertexMeshLayoutShaderByteCodeAndSize(&shader_byte_code, &size_shader);
	delete m_vb;
	m_vb = graphEngine->createVertexBuffer(vertexList, sizeof(vertex), size_list, shader_byte_code, size_shader);
}
