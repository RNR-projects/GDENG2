#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "RenderSystem.h"
#include "TextureManager.h"

class GraphicsEngine
{
public:
	static GraphicsEngine* getInstance();
	static void intialize();
	static void destroy();

	RenderSystem* getRenderSystem();
	TextureManager* getTextureManager();

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
};

