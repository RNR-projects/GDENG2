#pragma once
#include "ResourceManager.h"

class MeshManager : public ResourceManager
{
public:
	MeshManager();
	~MeshManager();

	Mesh* creatMeshFromFile(const wchar_t* file_path);
protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path) override;
};

