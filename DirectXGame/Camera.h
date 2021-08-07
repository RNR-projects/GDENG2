#pragma once
#include "AGameObject.h"
#include "InputListener.h"

class Camera : public AGameObject, public InputListener
{
public:
	Camera(std::string name);
	~Camera();

	virtual void update(float deltaTime) override;
	Matrix4x4 getViewMatrix();

	virtual void draw(ConstantBuffer* cb) override;

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point& delta_mouse_pos) override;

	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;

private:
	virtual void updateVertexLocations() override;

	float moveForward = 0.0f;
	float moveRight = 0.0f;
	float moveUp = 0.0f;
	Matrix4x4 viewMatrix;
	
	float m_deltaTime = 0;

	bool adjustingCam = false;
};

