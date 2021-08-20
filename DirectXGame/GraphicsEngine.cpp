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

	return true;
}

bool GraphicsEngine::release()
{
	m_render_system->release();
	delete m_render_system;
	delete m_tex_manager;
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
