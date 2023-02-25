#pragma once

#include "Vector.h"
#include <cstring>

namespace Hemy
{
	class HEMY_API Mat4
	{
	public:
		Mat4(float value = 1.0f)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if(i == j)
						m_Values[i][j] = value;
					else
						m_Values[i][j] = 0.0f;
				}
			}
		}
		Mat4(float values[4][4])
		{
			memcpy(m_Values, values, sizeof(float) * 16);
		}

		inline float* GetValues() { return &m_Values[0][0]; }

	public:

		inline float* operator[](int i) { return m_Values[i]; }
		inline const float* operator[](int i) const { return m_Values[i]; }

		Mat4 operator*(const Mat4& other) const
		{
			Mat4 result;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					float sum = 0.0f;
					for (int k = 0; k < 4; k++)
					{
						sum += m_Values[i][k] * other[k][j];
					}
					result[i][j] = sum;
				}
			}
			return result;
		}

		Vec4 operator*(const Vec4& vec) const
		{
			Vec4 result;

			for (int i = 0; i < 4; i++)
			{
				float sum = 0.0f;
				for (int j = 0; j < 4; j++)
				{
					sum += m_Values[i][j] * vec[j];
				}

				result[i] = sum;
			}

			return result;
		}
		
		static Mat4 Identity() { return Mat4(1.0f); }

		static Mat4 Translate(const Mat4& model, const Vec3& position)
		{
			Mat4 translationMatrix(1.0f);

			translationMatrix[0][3] = position.x;
			translationMatrix[1][3] = position.y;
			translationMatrix[2][3] = position.z;

			return translationMatrix * model;
		}

		static Mat4 Scale(const Mat4& model, const Vec3& scale)
		{
			Mat4 scaleMatrix(1.0f);

			scaleMatrix[0][0] = scale.x;
			scaleMatrix[1][1] = scale.y;
			scaleMatrix[2][2] = scale.z;

			return scaleMatrix * model;
		}

		static Mat4 Rotate(const Mat4& model, float radians, const Vec3& direction)
		{
			Mat4 rotation(1.0f);

			float c = cos(radians);
			float s = sin(radians);
			float t = 1 - c;

			Vec3 axis = direction.Normalized();
			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			rotation[0][0] = c + x * x * t;
			rotation[1][1] = c + y * y * t;
			rotation[2][2] = c + z * z * t;

			float tmp1 = x * y * t;
			float tmp2 = z * s;
			rotation[1][0] = tmp1 + tmp2;
			rotation[0][1] = tmp1 - tmp2;

			tmp1 = x * z * t;
			tmp2 = y * s;
			rotation[2][0] = tmp1 - tmp2;
			rotation[0][2] = tmp1 + tmp2;

			tmp1 = y * z * t;
			tmp2 = x * s;
			rotation[2][1] = tmp1 + tmp2;
			rotation[1][2] = tmp1 - tmp2;

			return rotation * model;
		}


		static Mat4 Ortho(float left, float right, float bottom, float up, float near, float far)
		{
			Mat4 result;

			float rl = right - left;
			float tb = up - bottom;
			float fn = far - near;

			result.m_Values[0][0] = 2.0f / rl;
			result.m_Values[1][1] = 2.0f / tb;
			result.m_Values[2][2] = -2.0f / fn;
			result.m_Values[3][0] = -(right + left) / rl;
			result.m_Values[3][1] = -(up + bottom) / tb;
			result.m_Values[3][2] = -(far + near) / fn;

			return result;
		}

	private:
		float m_Values[4][4];
	};
}