#pragma once

#include <cmath>
#include "Core.h"

namespace Hemy
{
	struct HEMY_API Vec4
	{
	public:
		float x;
		float y;
		float z;
		float w;

	public:
		Vec4(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w) { }
		Vec4(float value)
			: x(value), y(value), z(value), w(value) { }
		Vec4()
			: x(0), y(0), z(0), w(0) { }

		inline float Magnitude() const { return sqrtf(x * x + y * y + z * z + w * w); }
		Vec4 Normalized() const
		{
			float mag = Magnitude();
			if (mag == 0) return Vec4::Zero();

			return Vec4(
				x / mag, y / mag, z / mag, w / mag
			);
		}

		void Normalize()
		{
			Vec4 normalized = Normalized();
			x = normalized.x;
			y = normalized.y;
			z = normalized.z;
			w = normalized.w;
		}

		Vec4 operator *(Vec4 other)
		{
			return Vec4(
				x * other.x,
				y * other.y,
				z * other.z,
				w * other.w
			);
		}

		Vec4 operator *(float scalar) const
		{
			return Vec4(
				x * scalar,
				y * scalar,
				z * scalar,
				w * scalar
			);
		}

		inline float& operator[](int i)
		{
			if (i < 0) return x;
			if (i > 4) return w;

			switch (i)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			default:
			case 3: return w;
			}
		}

		inline const float& operator[](int i) const
		{
			if (i < 0) return x;
			if (i > 4) return w;

			switch (i)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			default:
			case 3: return w;
			}
		}

		inline bool operator ==(Vec4 other) { return x == other.x && y == other.y && z == other.z && w == other.w; }
		inline bool operator !=(Vec4 other) { return x != other.x || y != other.y || z != other.z || w != other.w; }
		inline bool operator !() { return x == 0 && y == 0 && z == 0 && w == 0; }

	public:
		static Vec4 Zero() { return Vec4(0); }
		static Vec4 One() { return Vec4(1); }
	};

	struct HEMY_API Vec3
	{
	public:
		float x; 
		float y;
		float z;

	public:
		Vec3(float x, float y, float z)
			: x(x), y(y), z(z) { }
		Vec3(float value)
			: x(value), y(value), z(value) { }
		Vec3()
			: x(0), y(0), z(0) { }

		inline float Magnitude() const { return sqrtf(x * x + y * y + z * z); }
		Vec3 Normalized() const 
		{
			float mag = Magnitude();
			if (mag == 0) return Vec3::Zero();

			return Vec3(
				x / mag, y / mag, z / mag
			);
		}

		void Normalize()
		{
			Vec3 normalized = Normalized();
			x = normalized.x;
			y = normalized.y;
			z = normalized.z;
		}

		Vec3 operator *(Vec3 other)
		{
			return Vec3(
				x * other.x,
				y * other.y,
				z * other.z
			);
		}

		Vec3 operator *(float scalar)
		{
			return Vec3(
				x * scalar,
				y * scalar,
				z * scalar
			);
		}

		Vec3 operator-()
		{
			return Vec3(
				-x,
				-y,
				-z
			);
		}

		inline bool operator ==(Vec3 other) { return x == other.x && y == other.y && z == other.z; }
		inline bool operator !=(Vec3 other) { return x != other.x || y != other.y || z != other.z; }
		inline bool operator !() { return x == 0 && y == 0 && z == 0; }

	public:
		static Vec3 Zero() { return Vec3(0); }
		static Vec3 One() { return Vec3(1); }
		static Vec3 Up() { return Vec3(0, 1, 0); }
		static Vec3 Down() { return Vec3(0, -1, 0); }
		static Vec3 Left() { return Vec3(-1, 0, 0); }
		static Vec3 Right() { return Vec3(1, 0, 0); }
		static Vec3 Forward() { return Vec3(0, 0, 1); }
		static Vec3 Back() { return Vec3(0, 0, -1); }
	};

	struct HEMY_API Vec2
	{
	public:
		float x;
		float y;

	public:
		Vec2(float x, float y)
			: x(x), y(y) { }
		Vec2(float value)
			: x(value), y(value) { }
		Vec2()
			: x(0), y(0) { }

		inline float Magnitude() const { return sqrtf(x * x + y * y); }
		Vec2 Normalized() const
		{
			float mag = Magnitude();
			if (mag == 0) return Vec2::Zero();

			return Vec2(
				x / mag, y / mag
			);
		}

		void Normalize()
		{
			Vec2 normalized = Normalized();
			x = normalized.x;
			y = normalized.y;
		}

		Vec2 operator *(Vec2 other)
		{
			return Vec2(
				x * other.x,
				y * other.y
			);
		}

		Vec2 operator *(float scalar)
		{
			return Vec2(
				x * scalar,
				y * scalar
			);
		}

		inline bool operator ==(Vec2 other) { return x == other.x && y == other.y; }
		inline bool operator !=(Vec2 other) { return x != other.x || y != other.y; }
		inline bool operator !() { return x == 0 && y == 0; }

	public:
		static Vec2 Zero() { return Vec2(0); }
		static Vec2 One() { return Vec2(1); }
		static Vec2 Up() { return Vec2(0, 1); }
		static Vec2 Down() { return Vec2(0, -1); }
		static Vec2 Left() { return Vec2(-1, 0); }
		static Vec2 Right() { return Vec2(1, 0); }
	};
}