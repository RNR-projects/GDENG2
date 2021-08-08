#include "Camera.h"
#include "InputSystem.h"

Camera::Camera(std::string name) : AGameObject(name)
{
	InputSystem::getInstance()->addListener(this);
	viewMatrix.setIdentity();
}

Camera::~Camera()
{
}

void Camera::update(float deltaTime)
{
	m_deltaTime = deltaTime;

	Vector3D newPos = this->localPosition + viewMatrix.getZDirection() * moveForward * 2.0f * deltaTime + 
		viewMatrix.getXDirection() * moveRight * 2.0f * deltaTime + viewMatrix.getYDirection() * moveUp * 2.0f * deltaTime;

	this->setPosition(newPos);
}

Matrix4x4 Camera::getViewMatrix()
{
	Matrix4x4 worldCam;
	worldCam.setIdentity();
	
	Matrix4x4 temp;

	temp.setIdentity();
	temp.setRotationX(this->localRotation.x);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationY(this->localRotation.y);
	worldCam *= temp;

	temp.setTranslation(this->localPosition);
	worldCam *= temp;

	viewMatrix = worldCam;
	worldCam.invert();

	return worldCam;
}

void Camera::draw(ConstantBuffer* cb)
{
}

void Camera::updateVertexLocations()
{
}

void Camera::onKeyDown(int key)
{
	if (adjustingCam) {
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
		if (key == 'Q')
		{
			moveUp = -1.0f;
		}
		else if (key == 'E')
		{
			moveUp = 1.0f;
		}
	}
}

void Camera::onKeyUp(int key)
{
	if (key == 'W' || key == 'S')
	{
		moveForward = 0;
	}
	if (key == 'A' || key == 'D')
	{
		moveRight = 0;
	}
	if (key == 'Q' || key == 'E')
	{
		moveUp = 0;
	}
}

void Camera::onMouseMove(const Point& delta_mouse_pos)
{
	if (adjustingCam) {
		this->setRotation(Vector3D(this->localRotation.x + delta_mouse_pos.y * m_deltaTime * 0.25f,
			this->localRotation.y + delta_mouse_pos.x * m_deltaTime * 0.25f, this->localRotation.z));
	}
}

void Camera::onLeftMouseDown(const Point& mouse_pos)
{
}

void Camera::onLeftMouseUp(const Point& mouse_pos)
{
}

void Camera::onRightMouseDown(const Point& mouse_pos)
{
	adjustingCam = true;
}

void Camera::onRightMouseUp(const Point& mouse_pos)
{
	adjustingCam = false;
}

Vector3D Camera::getForwardVector()
{
	return viewMatrix.getZDirection();
}
