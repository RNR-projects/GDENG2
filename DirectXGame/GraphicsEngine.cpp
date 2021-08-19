#include "GraphicsEngine.h"
#include "RenderSystem.h"

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
	return true;
}

bool GraphicsEngine::release()
{
	m_render_system->release();
	delete m_render_system;
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
