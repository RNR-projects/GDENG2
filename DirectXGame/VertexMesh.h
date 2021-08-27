#pragma once
#include "Vector2D.h"
#include "Vector3D.h"

class VertexMesh
{
public:
	VertexMesh() : m_position(), m_texcoord()
	{

	}

	VertexMesh(Vector3D position, Vector2D texcoord) : m_position(position), m_texcoord(texcoord)
	{

	}

	VertexMesh(const VertexMesh& vertexMesh) : m_position(vertexMesh.m_position), m_texcoord(vertexMesh.m_texcoord)
	{

	}

	~VertexMesh()
	{

	}

	Vector3D m_position;
	Vector2D m_texcoord;
};