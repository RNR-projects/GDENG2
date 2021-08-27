#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "RenderSystem.h"
#include "TextureManager.h"
#include "MeshManager.h"

class GraphicsEngine
{
public:
	static GraphicsEngine* getInstance();
	static void intialize();
	static void destroy();

	RenderSystem* getRenderSystem();
	TextureManager* getTextureManager();
	MeshManager* getMeshManager();

	void getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size);

private:
	GraphicsEngine();
	~GraphicsEngine();
	GraphicsEngine(GraphicsEngine const&) {};
	GraphicsEngine& operator=(GraphicsEngine const&) {};
	static GraphicsEngine* sharedInstance;

	bool init();
	bool release();

	TextureManager* m_tex_manager = nullptr;
	RenderSystem* m_render_system = nullptr;
	MeshManager* m_mesh_manager = nullptr;

	unsigned char m_mesh_layout_byte_code[1024];
	size_t m_mesh_layout_size = 0;
};

