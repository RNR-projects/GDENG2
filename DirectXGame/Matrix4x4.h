#pragma once
#include <memory>
#include "Vector3D.h"
#include "Matrix3x3.h"

class Matrix4x4
{
public:
	Matrix4x4()
	{

	}

	Matrix4x4(float values[4][4])
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				mat[i][j] = values[i][j];
	}

	Matrix4x4(const Matrix4x4& matrix)
	{
		::memcpy(mat, matrix.mat, sizeof(float) * 16);
	}

	void setIdentity() 
	{
		::memset(mat, 0, sizeof(float) * 16);
		mat[0][0] = 1;
		mat[1][1] = 1;
		mat[2][2] = 1;
		mat[3][3] = 1;
	}

	void setTranslation(const Vector3D& translation) 
	{
		setIdentity();
		mat[3][0] = translation.x;
		mat[3][1] = translation.y;
		mat[3][2] = translation.z;
	}
	
	void setScale(const Vector3D& scale) 
	{
		setIdentity();
		mat[0][0] = scale.x;
		mat[1][1] = scale.y;
		mat[2][2] = scale.z;
	}

	void setRotationX(float x)
	{
		setIdentity();
		mat[1][1] = cos(x);
		mat[1][2] = sin(x);
		mat[2][1] = -sin(x);
		mat[2][2] = cos(x);
	}
	
	void setRotationY(float y)
	{
		setIdentity();
		mat[0][0] = cos(y);
		mat[0][2] = -sin(y);
		mat[2][0] = sin(y);
		mat[2][2] = cos(y);
	}

	void setRotationZ(float z)
	{
		setIdentity();
		mat[0][0] = cos(z);
		mat[0][1] = sin(z);
		mat[1][0] = -sin(z);
		mat[1][1] = cos(z);
	}

	Matrix3x3 removeRowCol(int row, int col)
	{
		float leftover[3][3];
		int x = 0;
		int y = 0;
		for (int i = 0; i < 4; i++)
		{
			if (i != row)
			{
				x = 0;
				for (int j = 0; j < 4; j++)
				{
					if (j != col)
					{
						leftover[y][x] = mat[i][j];
						x++;
					}
				}
				y++;
			}
		}

		return Matrix3x3(leftover);
	}

	void operator *=(const Matrix4x4& matrix)
	{
		Matrix4x4 out;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out.mat[i][j] = mat[i][0] * matrix.mat[0][j] + mat[i][1] * matrix.mat[1][j] + mat[i][2] * matrix.mat[2][j] + mat[i][3] * matrix.mat[3][j];
			}
		}

		::memcpy(mat, out.mat, sizeof(float) * 16);
	}
	
	void operator *=(const float& scalar)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				mat[i][j] *= scalar;
			}
		}
	}

	Vector3D operator *(const Vector3D& vector)
	{
		Vector3D v;

		v.x = vector.x * mat[0][0] + mat[0][1] * vector.y + mat[0][2] * vector.z + mat[0][3];
		v.y = vector.x * mat[1][0] + mat[1][1] * vector.y + mat[1][2] * vector.z + mat[1][3];
		v.z = vector.x * mat[2][0] + mat[2][1] * vector.y + mat[2][2] * vector.z + mat[2][3];

		return v;
	}

	Vector3D getZDirection()
	{
		return Vector3D(mat[2][0], mat[2][1], mat[2][2]);
	}
	
	Vector3D getXDirection()
	{
		return Vector3D(mat[0][0], mat[0][1], mat[0][2]);
	}
	
	Vector3D getYDirection()
	{
		return Vector3D(mat[1][0], mat[1][1], mat[1][2]);
	}
	
	Vector3D getTranslation()
	{
		return Vector3D(mat[3][0], mat[3][1], mat[3][2]);
	}

	void setPerspectiveFovLH(float fov, float aspect, float znear, float zfar)
	{
		setIdentity();

		float yScale = 1.0f / tanf(fov / 2.0f);
		float xScale = yScale / aspect;
		mat[0][0] = xScale;
		mat[1][1] = yScale;
		mat[2][2] = zfar / (zfar - znear);
		mat[2][3] = 1.0f;
		mat[3][2] = (-znear * zfar) / (zfar - znear);
	}

	void setOrthoLH(float width, float height, float near_plane, float far_plane)
	{
		setIdentity();
		mat[0][0] = 2.0f / width;
		mat[1][1] = 2.0f / height;
		mat[2][2] = 1.0f / (far_plane - near_plane);
		mat[3][2] = -(near_plane / (far_plane - near_plane));
	}

	void invert()
	{
		Matrix4x4 out;
		float determinant = mat[0][0] * removeRowCol(0, 0).getDeterminant() - mat[1][0] * removeRowCol(1, 0).getDeterminant()
			+ mat[2][0] * removeRowCol(2, 0).getDeterminant() - mat[3][0] * removeRowCol(3, 0).getDeterminant();

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out.mat[i][j] = pow(-1, i + j) * removeRowCol(j, i).getDeterminant();
			}
		}

		out *= (1 / determinant);

		::memcpy(mat, out.mat, sizeof(float) * 16);
	}

	~Matrix4x4()
	{

	}

	float mat[4][4] = {};
};