#include "Sphere.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "IndexBuffer.h"
#include "BoundingSphere.h"
#include "RenderSystem.h"
#include "Texture.h"
#include "PhysicsComponent.h"

#define PI 3.14159265

Sphere::Sphere(std::string name, Vector3D pos, float radius, int tessellationLevel) : AGameObject(name, AGameObject::PrimitiveType::SPHERE)
{
	this->localPosition = pos;
	this->radius = radius;
	this->tessellationLevel = tessellationLevel;

	m_wood_tex = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\brick.png");

	generateEdgesAtTessellation(tessellationLevel);

	RenderSystem* graphEngine = GraphicsEngine::getInstance()->getRenderSystem();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	std::vector<Vector3D> worldLocations = getVertexWorldPositions();

	vertex* vertexList = (vertex*)malloc(sizeof(vertex) * edges.size());

	for (int i = 0; i < edges.size(); i++)
	{
		vertexList[i] = {worldLocations[i], texCoords[i]};
	}

	UINT size_list = edges.size();

	m_vs = graphEngine->createVertexShader(shader_byte_code, size_shader);

	m_vb = graphEngine->createVertexBuffer(vertexList, sizeof(vertex), size_list, shader_byte_code, size_shader);

	graphEngine->releaseCompiledShader();

	graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = graphEngine->createPixelShader(shader_byte_code, size_shader);

	graphEngine->releaseCompiledShader();

	free(vertexList);
}

Sphere::~Sphere()
{
	delete m_vb;
	delete m_vs;
	delete m_ps;
	delete m_ib;
}

void Sphere::update(float deltaTime)
{
}

void Sphere::draw(ConstantBuffer* cb)
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

void Sphere::setRadius(float newRadius)
{
	this->radius = newRadius;

	updateVertexLocations();
}

void Sphere::setTessellationLevel(int newTessellationLevel)
{
	this->tessellationLevel = newTessellationLevel;

	updateVertexLocations();
}

float Sphere::getRadius()
{
	return this->radius;
}

std::vector<Vector3D> Sphere::getVertexWorldPositions()
{
	std::vector<Vector3D> out;
	for (int i = 0; i < edges.size(); i++)
	{
		out.push_back(Quaternion::rotatePointEuler(Vector3D(edges[i].x * localScale.x, edges[i].y * localScale.y, edges[i].z * localScale.z), this->localRotation) + this->localPosition);
	}
    return out;
}

void Sphere::updateVertexLocations()
{
	RenderSystem* graphEngine = GraphicsEngine::getInstance()->getRenderSystem();

	generateEdgesAtTessellation(tessellationLevel);

	std::vector<Vector3D> worldLocations = getVertexWorldPositions();

	vertex* vertexList = (vertex*)malloc(sizeof(vertex) * edges.size());

	for (int i = 0; i < edges.size(); i++)
	{
		vertexList[i] = { worldLocations[i], texCoords[i] };
	}

	UINT size_list = edges.size();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::getInstance()->getVertexMeshLayoutShaderByteCodeAndSize(&shader_byte_code, &size_shader);
	delete m_vb;
	m_vb = graphEngine->createVertexBuffer(vertexList, sizeof(vertex), size_list, shader_byte_code, size_shader);
}

void Sphere::generateEdgesAtTessellation(int tessellation)
{
	edges.clear();
	texCoords.clear();
	int arcVertexCount = pow(2, tessellation - 1);

	edges.push_back(Vector3D(0, radius, 0));
	texCoords.push_back(Vector2D(0.125f, 0));
	edges.push_back(Vector3D(0, radius, 0));
	texCoords.push_back(Vector2D(0.375f, 0));
	edges.push_back(Vector3D(0, radius, 0));
	texCoords.push_back(Vector2D(0.625f, 0));
	edges.push_back(Vector3D(0, radius, 0));
	texCoords.push_back(Vector2D(0.875f, 0));
	float anglePerVVertex = PI / (2.0f * arcVertexCount);
	for (int i = 1; i < arcVertexCount; i++)
	{
		float anglePerHVertex = 2.0f / (float)(i * 4) * PI;
		for (int j = 0; j < i * 4; j++)
		{
			edges.push_back(Vector3D(radius * sin(anglePerHVertex * j) * sin(anglePerVVertex * i), radius * cos(anglePerVVertex * i), radius * cos(anglePerHVertex * j) * sin(anglePerVVertex * i)));
			texCoords.push_back(Vector2D(1.0f / (float)(i * 4) * j, 0.5f / (float)arcVertexCount * i));
		}
		edges.push_back(Vector3D(radius * sin(0) * sin(anglePerVVertex * i), radius * cos(anglePerVVertex * i), radius * cos(0) * sin(anglePerVVertex * i)));
		texCoords.push_back(Vector2D(1.0f, 0.5f / (float)arcVertexCount * i));
	}
	for (int i = 0; i < arcVertexCount; i++)
	{
		float anglePerHVertex = 2.0f / (float)((arcVertexCount - i) * 4) * PI;
		for (int j = 0; j < (arcVertexCount - i) * 4; j++)
		{
			edges.push_back(Vector3D(radius * sin(anglePerHVertex * j) * sin(PI / 2.0f + anglePerVVertex * i), radius * cos(PI / 2.0f + anglePerVVertex * i), radius * cos(anglePerHVertex * j) * sin(PI / 2.0f + anglePerVVertex * i)));
			texCoords.push_back(Vector2D(1.0f / (float)((arcVertexCount - i) * 4) * j, 0.5f / (float)arcVertexCount * i + 0.5f));
		}
		edges.push_back(Vector3D(radius * sin(0) * sin(PI / 2.0f + anglePerVVertex * i), radius * cos(PI / 2.0f + anglePerVVertex * i), radius * cos(0) * sin(PI / 2.0f + anglePerVVertex * i)));
		texCoords.push_back(Vector2D(1.0f, 0.5f / (float)arcVertexCount * i + 0.5f));
	}
	edges.push_back(Vector3D(0, -radius, 0));
	texCoords.push_back(Vector2D(0.125f, 1));
	edges.push_back(Vector3D(0, -radius, 0));
	texCoords.push_back(Vector2D(0.375f, 1));
	edges.push_back(Vector3D(0, -radius, 0));
	texCoords.push_back(Vector2D(0.625f, 1));
	edges.push_back(Vector3D(0, -radius, 0));
	texCoords.push_back(Vector2D(0.875f, 1));

	UINT size_index_list = arcVertexCount * arcVertexCount * 24;
	unsigned int* index_list = (unsigned int*) malloc(sizeof(unsigned int) * size_index_list);

	int currentIndex = 0;
	int layerIndex = 0;
	for (int i = 0; i < 4; i++)
	{
		index_list[currentIndex] = (unsigned int)i;
		index_list[currentIndex + 1] = (unsigned int)(i + 4);
		index_list[currentIndex + 2] = (unsigned int)(i + 5);
		currentIndex += 3;
	}
	layerIndex = 4;
	for (int i = 1; i < arcVertexCount; i++)
	{
		int x = 1;
		for (int k = 0; k < 4; k++)
		{
			for (int j = 0; j < i; j++)
			{
				index_list[currentIndex] = (unsigned int)(layerIndex + j + 1 + k * i);
				index_list[currentIndex + 1] = (unsigned int)(layerIndex + j + k * i);
				index_list[currentIndex + 2] = (unsigned int)(layerIndex + (i * 4) + 1 + x);
				x++;
				currentIndex += 3;
			}
			x++;
		}
		x = 0;
		for (int k = 0; k < 4; k++)
		{
			for (int j = 0; j < i + 1; j++)
			{
				index_list[currentIndex] = (unsigned int)(layerIndex + j + k * i);
				index_list[currentIndex + 1] = (unsigned int)(layerIndex + (i * 4) + 1 + x);
				index_list[currentIndex + 2] = (unsigned int)(layerIndex + (i * 4) + 2 + x);
				x++;
				currentIndex += 3;
			}
		}
		layerIndex += i * 4 + 1;
	}
	for (int i = 0; i < arcVertexCount - 1; i++)
	{
		int x = 1;
		for (int k = 0; k < 4; k++)
		{
			for (int j = 0; j < arcVertexCount - i - 1; j++)
			{
				index_list[currentIndex] = (unsigned int)(layerIndex + x);
				index_list[currentIndex + 1] = (unsigned int)(layerIndex + ((arcVertexCount - i) * 4) + 1 + j + k * (arcVertexCount - i - 1));
				index_list[currentIndex + 2] = (unsigned int)(layerIndex + ((arcVertexCount - i) * 4) + 2 + j + k * (arcVertexCount - i - 1));
				x++;
				currentIndex += 3;
			}
			x++;
		}
		x = 0;
		for (int k = 0; k < 4; k++)
		{
			for (int j = 0; j < arcVertexCount - i; j++)
			{
				index_list[currentIndex] = (unsigned int)(layerIndex + x + 1);
				index_list[currentIndex + 1] = (unsigned int)(layerIndex + x);
				index_list[currentIndex + 2] = (unsigned int)(layerIndex + ((arcVertexCount - i) * 4) + 1 + j + k * (arcVertexCount - i - 1));
				x++;
				currentIndex += 3;
			}
		}
		layerIndex += (arcVertexCount - i) * 4 + 1;
	}
	for (int i = 0; i < 4; i++)
	{
		index_list[currentIndex + 2] = (unsigned int)(edges.size() + i - 4);
		index_list[currentIndex + 1] = (unsigned int)(layerIndex + i);
		index_list[currentIndex] = (unsigned int)(layerIndex + i + 1);
		currentIndex += 3;
	}
	
	m_ib = GraphicsEngine::getInstance()->getRenderSystem()->createIndexBuffer(index_list, size_index_list);

	free(index_list);
}
