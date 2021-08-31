#pragma once
#include "Resource.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <vector>
#include "Vector3D.h"

class Mesh : public Resource
{
public:
	Mesh(const wchar_t* fullPath);
	~Mesh();

	VertexBuffer* getVertexBuffer();
	IndexBuffer* getIndexBuffer();

	void scaleVertexLocations(Vector3D scale);
	void rotateVertexLocations(Vector3D rot);
	void moveVertexLocations(Vector3D pos);

private:
	VertexBuffer* m_vertex_buffer;
	IndexBuffer* m_index_buffer;

	void updateVertexLocations();

	Vector3D position;
	Vector3D rotation;
	Vector3D scale;

	std::vector<class VertexMesh> list_vertices;

	friend class DeviceContext;
};

