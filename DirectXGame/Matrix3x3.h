#pragma once
#include <memory>
#include "Vector3D.h"

class Matrix3x3
{
public:
	Matrix3x3()
	{

	}

	Matrix3x3(float values[3][3])
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				mat[i][j] = values[i][j];
	}

	void setIdentity()
	{
		::memset(mat, 0, sizeof(float) * 9);
		mat[0][0] = 1;
		mat[1][1] = 1;
		mat[2][2] = 1;
	}

	void operator *=(const Matrix3x3& matrix)
	{
		Matrix3x3 out;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				out.mat[i][j] = mat[i][0] * matrix.mat[0][j] + mat[i][1] * matrix.mat[1][j] + mat[i][2] * matrix.mat[2][j];
			}
		}

		::memcpy(mat, out.mat, sizeof(float) * 9);
	}

	float getDeterminant()
	{
		float determinant = 0;
		float diagonal;

		for (int i = 0; i < 3; i++)
		{
			diagonal = 1;
			for (int j = 0; j < 3; j++)
			{
				diagonal *= mat[(i + j) % 3][j];
			}

			determinant += diagonal;
		}
		
		for (int i = 2; i > -1; i--)
		{
			diagonal = 1;
			for (int j = 0; j < 3; j++)
			{
				diagonal *= mat[(i - j + 3) % 3][j];
			}

			determinant -= diagonal;
		}

		return determinant;
	}

	~Matrix3x3()
	{

	}

	float mat[3][3] = {};
};