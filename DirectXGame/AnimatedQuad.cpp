#include "AnimatedQuad.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "IndexBuffer.h"
#include <cmath>

AnimatedQuad::AnimatedQuad()
{
}

AnimatedQuad::~AnimatedQuad()
{
	m_vb->release();
	m_vs->release();
	m_ps->release();
	m_ib->release();
}

void AnimatedQuad::draw(ConstantBuffer* cb, float deltaTime)
{
	this->totalElapsedTime += deltaTime;
	this->deltaTime += deltaTime;
	this->speed = 4.0f + sinf(this->deltaTime / 3.0f) * 3.0f;

	updateVertexLocations();

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, cb);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void AnimatedQuad::createQuad(Vector3D edge[4], Vector3D edge2[4], Vector3D colors[4], Vector3D colors2[4])
{
	for (int i = 0; i < 4; i++)
	{
		this->edges[i] = edge[i];
		this->edges2[i] = edge2[i];
		this->colors[i] = colors[i];
		this->colors2[i] = colors2[i];
	}

	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);


	vertex list[] = {
		{edge[0],	this->colors[0]},
		{edge[1],	this->colors[1]},
		{edge[2],	this->colors[2]},
		{edge[3],	this->colors[3]}
	};

	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();

	UINT size_list = ARRAYSIZE(list);

	unsigned int index_list[] = {
		0,1,2,
		1,2,3
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

void AnimatedQuad::updateVertexLocations()
{
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	Vector3D newEdges[4];
	Vector3D newColors[4];
	for (int i = 0; i < 4; i++)
	{
		newEdges[i] = Vector3D::lerp(edges[i], edges2[i], ((1 + sinf(totalElapsedTime)) / 2.0f));
		newColors[i] = Vector3D::lerp(colors[i], colors2[i], ((1 + sinf(totalElapsedTime)) / 2.0f));
	}

	vertex list[] = {
		{ newEdges[0],		newColors[0] },
		{ newEdges[1],		newColors[1] },
		{ newEdges[2],		newColors[2] },
		{ newEdges[3],		newColors[3] }
	};

	UINT size_list = ARRAYSIZE(list);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->releaseCompiledShader();
}
