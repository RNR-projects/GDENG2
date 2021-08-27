#include "GraphicsEngine.h"

GraphicsEngine* GraphicsEngine::sharedInstance = nullptr;

GraphicsEngine::GraphicsEngine()
{
}

GraphicsEngine::~GraphicsEngine()
{
}

bool GraphicsEngine::init()
{
	m_render_system = new RenderSystem();
	m_render_system->init();
	m_tex_manager = new TextureManager();
	m_mesh_manager = new MeshManager();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	m_render_system->compileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	::memcpy(m_mesh_layout_byte_code, shader_byte_code, size_shader);
	m_mesh_layout_size = size_shader;
	m_render_system->releaseCompiledShader();

	return true;
}

bool GraphicsEngine::release()
{
	m_render_system->release();
	delete m_render_system;
	delete m_tex_manager;
	delete m_mesh_manager;
	return true;
}

GraphicsEngine* GraphicsEngine::getInstance()
{
	if (sharedInstance == nullptr)
		GraphicsEngine::intialize();
	return sharedInstance;
}

void GraphicsEngine::intialize()
{
	sharedInstance = new GraphicsEngine();
	sharedInstance->init();
}

void GraphicsEngine::destroy()
{
	if (sharedInstance != nullptr)
		sharedInstance->release();
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return m_render_system;
}

TextureManager* GraphicsEngine::getTextureManager()
{
	return m_tex_manager;
}

MeshManager* GraphicsEngine::getMeshManager()
{
	return m_mesh_manager;
}

void GraphicsEngine::getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size)
{
	*byte_code = m_mesh_layout_byte_code;
	*size = m_mesh_layout_size;
}
