#include "AppWindow.h"
#include <Windows.h>
#include "GameObjectConstants.h"
#include "InputSystem.h"
#include <iostream>
#include <random>

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

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	Vector3D convertedPos = Vector3D((float)point.x / (float)width * 2.0f - 1.0f, -(float)point.y / (float)height * 2.0f + 1.0f, 0.0f);

	Matrix4x4 inverseProj(cc.m_proj);
	inverseProj.invert();
	Vector3D raycastEye = inverseProj * convertedPos;
	raycastEye.z = 0;

	Matrix4x4 inverseView(cc.m_view);
	inverseView.invert();
	Vector3D raycastWorld = inverseView * raycastEye;
	//raycastWorld.normalize();//normalize if we want direction vector for perspective raycast

	std::cout << raycastWorld.x << " " << raycastWorld.y << " " << raycastWorld.z << "\n";
	//ortho raycast comes from cursor straight forward along z
	//perspective raycast comes from camera position in the direction of raycast world
	/*if (quad1->checkRaycast(Vector3D(raycastWorld.x, raycastWorld.y, -4.0f), Vector3D(0, 0, 1)))
	{
		std::cout << "true \n";
		quad1->setColors(Vector3D(0, 0, 1));
	}
	else
	{
		std::cout << "false \n";
		quad1->setColors(Vector3D(1, 1, 0));
	}*/
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

void AppWindow::onMouseMove(const Point& mouse_pos)
{
	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	rot_x += (mouse_pos.y - height / 2.0f) * m_delta_time * 0.25f;
	rot_y += (mouse_pos.x - width / 2.0f) * m_delta_time * 0.25f;

	InputSystem::getInstance()->setCursorPosition(Point(width / 2.0f, height / 2.0f));
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		moveForward = 1.0f;
	}
	else if (key == 'S')
	{
		moveForward = -1.0f;
	}
	if (key == 'A')
	{
		moveRight = -1.0f;
	}
	else if (key == 'D')
	{
		moveRight = 1.0f;
	}
}

void AppWindow::onKeyUp(int key)
{
	if (key == 'W' || key == 'S')
	{
		moveForward = 0;
	}
	if (key == 'A' || key == 'D')
	{
		moveRight = 0;
	}
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

void AppWindow::update()
{
	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;

	m_delta_scale += m_delta_time / 0.5f;

	Matrix4x4 temp;

	/*temp.setRotationZ(0.0f);
	cc.m_world *= temp;
	
	temp.setRotationY(rot_y);
	cc.m_world *= temp;
	
	temp.setRotationX(rot_x);
	cc.m_world *= temp;*/

	//quad1->setRotation(Vector3D(rot_x, rot_y, 0));

	cc.m_world.setIdentity();

	Matrix4x4 new_cam;
	new_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(rot_x);
	new_cam *= temp;
	
	temp.setIdentity();
	temp.setRotationY(rot_y);
	new_cam *= temp;

	Vector3D newPos = worldCam.getTranslation() + new_cam.getZDirection() * moveForward * 0.3f + new_cam.getXDirection() * moveRight * 0.3f;

	temp.setTranslation(newPos);
	new_cam *= temp;
	
	worldCam = new_cam;
	new_cam.invert();

	cc.m_view = new_cam;

	m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);
}

void AppWindow::onCreate()
{
	Window::onCreate();

	InputSystem::getInstance()->addListener(this);
	InputSystem::getInstance()->showCursor(false);

	cc.m_view.setIdentity();
	worldCam.setTranslation(Vector3D(0, 0, -2));

	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	//cc.m_proj.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);

	cc.m_proj.setPerspectiveFovLH(1.57f, (float)width / (float)height, 0.1f, 100.0f);
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

	update();

	for (int i = 0; i < 1; i++)
	{
		this->cubes[i]->update(m_delta_time);
		this->cubes[i]->draw(m_cb);
	}
	//plane->draw(m_cb);
	//newQuad->draw(m_cb, EngineTime::getDeltaTime());

	m_swap_chain->present(true);

	m_previous_time = m_current_time;
	m_current_time = ::GetTickCount();
	m_delta_time = EngineTime::getDeltaTime();
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
	for (int i = 0; i < 1; i++)
	{
		Vector3D loc = Vector3D(rand() % 200 / 100.0f - 1.0f, rand() % 200 / 100.0f - 1.0f, rand() % 200 / 100.0f - 1.0f);
		Cube* cubey = new Cube("Cube " + i, Vector3D(), Vector3D(1,1,1), Vector3D(1, 1, 0), Vector3D());
		this->cubes.push_back(cubey);
	}
	plane = new Plane("Plane", Vector3D(0, -0.25f, 0), Vector3D(3, 1, 3), Vector3D(1, 1, 0), Vector3D(0,0,0));
	//newQuad = new AnimatedQuad();


	/*Vector3D list[4] = {
		Vector3D(-0.6f, -0.9f, 0),
		Vector3D(-0.9f, 0.0f, 0),
		Vector3D(1.0f, -0.25f, 0),
		Vector3D(-0.6f, -0.9f, 1.0f)
	};
	Vector3D list2[4] = {
		Vector3D(-0.25f, 0.0f, 0),
		Vector3D(0.0f, 0.75f, 0),
		Vector3D(0.0f, -0.75f, 0),
		Vector3D(0.75f, 0.75f, 0)
	};
	
	Vector3D color[4] = {
		Vector3D(0.5f, 0.0f, 0),
		Vector3D(1.0f, 1.0f, 0),
		Vector3D(0.0f, 0.0f, 1.0f),
		Vector3D(1.0f, 1.0f, 1.0f)
	};
	Vector3D color2[4] = {
		Vector3D(0.0f, 1.0f, 0),
		Vector3D(1.0f, 1.0f, 0),
		Vector3D(1.0f, 0.0f, 0),
		Vector3D(0.0f, 0.0f, 1.0f)
	};

	newQuad->createQuad(list, list2, color, color2);*/

	cc.m_time = 0;

	m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void AppWindow::initializeEngine()
{
}
