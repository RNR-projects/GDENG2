#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class GraphicsEngine
{
public:
	static GraphicsEngine* getInstance();
	static void intialize();
	static void destroy();

	RenderSystem* getRenderSystem();

private:
	GraphicsEngine();
	~GraphicsEngine();
	GraphicsEngine(GraphicsEngine const&) {};
	GraphicsEngine& operator=(GraphicsEngine const&) {};
	static GraphicsEngine* sharedInstance;

	bool init();
	bool release();

	RenderSystem* m_render_system = nullptr;
};

