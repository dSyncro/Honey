#pragma once

#include "Vector2.h"

namespace Honey::Math {

	struct Vector2Int {

		enum class Axis {
			X = 0,
			Y = 1
		};

		constexpr Vector2Int(int value = 0) : x(value), y(value) {}
		constexpr Vector2Int(int x, int y) : x(x), y(y) {}

		/* @brief Vector2Int(-1, 0) */
		static const Vector2Int& left();

		/** @brief Vector2Int(1, 0) */
		static const Vector2Int& right();

		/** @brief Vector2Int(0, 1) */
		static const Vector2Int& up();

		/** @brief Vector2Int(0, -1) */
		static const Vector2Int& down();

		/** @brief Vector2Int(0, 0) */
		static const Vector2Int& zero();

		/** @brief Vector2Int(1, 1) */
		static const Vector2Int& one();

		Vector2Int& set(int x, int y);
		Vector2Int& clamp(const Vector2Int& min, const Vector2Int& max);

		bool equals(const Vector2Int& other) const;
		float getMagnitude() const;
		float getSquaredMagnitude() const;

		static Vector2Int abs(const Vector2Int& vector);
		static Vector2Int sign(const Vector2Int& vector);
		static Vector2Int ceilToInt(const Vector2& vector);
		static Vector2Int floorToInt(const Vector2& vector);
		static Vector2Int roundToInt(const Vector2& vector);
		static Vector2Int max(const Vector2Int& a, const Vector2Int& b);
		static Vector2Int min(const Vector2Int& a, const Vector2Int& b);
		static Vector2Int scale(const Vector2Int& a, const Vector2Int& b);


		static float distance(const Vector2Int& a, const Vector2Int& b);
		static float squaredDistance(const Vector2Int& a, const Vector2Int& b);

		bool operator ==(const Vector2Int& other) const { return x == other.x && y == other.y; }
		bool operator !=(const Vector2Int& other) const { return !(*this == other); }

		Vector2Int operator +() const { return *this; }
		Vector2Int operator -() const { return Vector2Int(-x, -y); }

		Vector2Int operator +(const Vector2Int& other) const { return Vector2Int(x + other.x, y + other.y); }
		Vector2Int operator -(const Vector2Int& other) const { return Vector2Int(x - other.x, y - other.y); }
		Vector2Int operator *(int scalar) const { return Vector2Int(x * scalar, y * scalar); }
		Vector2Int operator *(const Vector2Int& other) const { return Vector2Int(x * other.x, y * other.y); }
		Vector2Int operator /(int scalar) const { return Vector2Int(x / scalar, y / scalar); }
		Vector2Int operator /(const Vector2Int& other) const { return Vector2Int(x / other.x, y / other.y); }

		// Assignment operators
		Vector2Int& operator +=(const Vector2Int& other);
		Vector2Int& operator -=(const Vector2Int& other);
		Vector2Int& operator *=(int scalar);
		Vector2Int& operator *=(const Vector2Int& other);
		Vector2Int& operator /=(int scalar);
		Vector2Int& operator /=(const Vector2Int& other);

		// Subscript operator
		int& operator [](int index) { return (Axis)index == Axis::X ? x : y; }
		int operator [](int index) const { return (Axis)index == Axis::X ? x : y; }
		int& operator [](Axis axis) { return axis == Axis::X ? x : y; }
		int operator [](Axis axis) const { return axis == Axis::X ? x : y; }

		operator Vector2() const { return Vector2(static_cast<float>(x), static_cast<float>(y)); }
		//operator Vector3Int() const { return Vector3Int(X, Y, 0); };

		int x, y;
	};

	static Vector2Int operator *(int scalar, const Vector2Int& vector) { return vector * scalar; }
}
