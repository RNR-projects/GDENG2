#pragma once
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "Quaternion.h"
#include <DirectXMath.h>
#include <DirectXCollision.h>

struct vertex {
	Vector3D position;
	Vector3D color;
};

__declspec(align(16))
struct constant {
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;

	unsigned int m_time;
};