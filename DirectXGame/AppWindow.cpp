#include "AppWindow.h"
#include <Windows.h>
#include "GameObjectConstants.h"
#include "InputSystem.h"
#include <iostream>

AppWindow* AppWindow::sharedInstance = nullptr;

AppWindow::AppWindow()
{
	
}

AppWindow::~AppWindow()
{
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
	POINT point = { mouse_pos.x, mouse_pos.y };
	ScreenToClient(this->m_hwnd, &point);

	Vector3D convertedPos = Vector3D((float)point.x / (float)WIDTH * 2.0f - 1.0f, -(float)point.y / (float)HEIGHT * 2.0f + 1.0f, 1.0f);

	Matrix4x4 inverseProj(cc.m_proj);
	inverseProj.invert();
	Vector3D raycastEye = inverseProj * convertedPos;
	raycastEye.z = 1;

	Matrix4x4 inverseView(cc.m_view);
	inverseView.invert();
	Vector3D raycastWorld = inverseView * raycastEye;
	raycastWorld.normalize();

	std::cout << raycastWorld.x << " " << raycastWorld.y << " " << raycastWorld.z << "\n";
	if (quad1->checkRaycast(Vector3D(0, 0, 0), raycastWorld))
	{
		std::cout << "true \n";
		quad1->setColors(Vector3D(0, 0, 1));
	}
	else
	{
		std::cout << "false \n";
		quad1->setColors(Vector3D(1, 1, 0));
	}
	//scale_cube = 0.5f;
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
	//scale_cube = 1.0f;
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
	//scale_cube = 2.0f;
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
	//scale_cube = 1.0f;
}

void AppWindow::onMouseMove(const Point& delta_mouse_pos)
{
	//rot_x -= delta_mouse_pos.y * m_delta_time;
	//rot_y -= delta_mouse_pos.x * m_delta_time;
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		rot_x += m_delta_time;
	}
	else if (key == 'S')
	{
		rot_x -= m_delta_time;
	}
	if (key == 'A')
	{
		rot_y += m_delta_time;
	}
	else if (key == 'D')
	{
		rot_y -= m_delta_time;
	}
}

void AppWindow::onKeyUp(int key)
{
}

AppWindow* AppWindow::getInstance()
{
	if (sharedInstance == nullptr)
		AppWindow::initialize();
	return sharedInstance;
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
	sharedInstance->init();
}

void AppWindow::destroy()
{
	if (sharedInstance != nullptr)
		sharedInstance->onDestroy();
}

void AppWindow::updatePosition()
{
	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;

	m_delta_scale += m_delta_time / 0.5f;

	Matrix4x4 temp;
	cc.m_world.setScale(Vector3D(scale_cube, scale_cube, scale_cube));

	/*temp.setRotationZ(0.0f);
	cc.m_world *= temp;
	
	temp.setRotationY(rot_y);
	cc.m_world *= temp;
	
	temp.setRotationX(rot_x);
	cc.m_world *= temp;*/

	quad1->setRotation(Vector3D(rot_x, rot_y, 0));

	m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);
}

void AppWindow::onCreate()
{
	Window::onCreate();

	InputSystem::getInstance()->addListener(this);

	cc.m_view.setIdentity();

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	cc.m_proj.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::getInstance()->update();

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(width, height);

	updatePosition();

	quad1->draw(m_cb);

	m_swap_chain->present(true);

	m_previous_time = m_current_time;
	m_current_time = ::GetTickCount();
	m_delta_time = (m_previous_time)?((m_current_time - m_previous_time) / 1000.0f):0;
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	m_swap_chain->release();
	GraphicsEngine::getInstance()->destroy();
}

void AppWindow::onFocus()
{
	InputSystem::getInstance()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::getInstance()->removeListener(this);
}

void AppWindow::createGraphicsWindow()
{
	GraphicsEngine::intialize();
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();
	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	m_swap_chain->init(this->m_hwnd, width, height);
	quad1 = new Quad();

	quad1->createQuad(Vector3D(-0.5f, 0.5f, 1.0f), Vector3D(0.25f, 0.25f, 0.25f), Vector3D(1, 1, 0));

	cc.m_time = 0;

	m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void AppWindow::initializeEngine()
{
}
