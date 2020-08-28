#pragma once

#include "Vector2.h"

namespace Honey::Math {

	struct Vector2Int {

		enum class Axis {
			X = 0,
			Y = 1
		};

		constexpr Vector2Int(int value = 0) : X(value), Y(value) {}
		constexpr Vector2Int(int x, int y) : X(x), Y(y) {}

		static const Vector2Int Left;             //!< @brief Vector2Int(-1, 0)
		static const Vector2Int Right;            //!< @brief Vector2Int(1, 0)
		static const Vector2Int Up;               //!< @brief Vector2Int(0, 1)
		static const Vector2Int Down;             //!< @brief Vector2Int(0, -1)
		static const Vector2Int Zero;             //!< @brief Vector2Int(0, 0)
		static const Vector2Int One;              //!< @brief Vector2Int(1, 1)

		Vector2Int& Set(int x, int y);
		Vector2Int& Clamp(const Vector2Int& min, const Vector2Int& max);

		bool Equals(const Vector2Int& other) const;
		float GetMagnitude() const;
		float GetSquaredMagnitude() const;

		static Vector2Int Abs(const Vector2Int& vector);
		static Vector2Int Sign(const Vector2Int& vector);
		static Vector2Int CeilToInt(const Vector2& vector);
		static Vector2Int FloorToInt(const Vector2& vector);
		static Vector2Int RoundToInt(const Vector2& vector);
		static Vector2Int Max(const Vector2Int& a, const Vector2Int& b);
		static Vector2Int Min(const Vector2Int& a, const Vector2Int& b);
		static Vector2Int Scale(const Vector2Int& a, const Vector2Int& b);


		static float Distance(const Vector2Int& a, const Vector2Int& b);
		static float SquaredDistance(const Vector2Int& a, const Vector2Int& b);

		bool operator ==(const Vector2Int& other) const { return X == other.X && Y == other.Y; }
		bool operator !=(const Vector2Int& other) const { return !(*this == other); }

		Vector2Int operator +() const { return *this; }
		Vector2Int operator -() const { return Vector2Int(-X, -Y); }

		Vector2Int operator +(const Vector2Int& other) const { return Vector2Int(X + other.X, Y + other.Y); }
		Vector2Int operator -(const Vector2Int& other) const { return Vector2Int(X - other.X, Y - other.Y); }
		Vector2Int operator *(int scalar) const { return Vector2Int(X * scalar, Y * scalar); }
		Vector2Int operator *(const Vector2Int& other) const { return Vector2Int(X * other.X, Y * other.Y); }
		Vector2Int operator /(int scalar) const { return Vector2Int(X / scalar, Y / scalar); }
		Vector2Int operator /(const Vector2Int& other) const { return Vector2Int(X / other.X, Y / other.Y); }

		// Assignment operators
		Vector2Int& operator +=(const Vector2Int& other);
		Vector2Int& operator -=(const Vector2Int& other);
		Vector2Int& operator *=(int scalar);
		Vector2Int& operator *=(const Vector2Int& other);
		Vector2Int& operator /=(int scalar);
		Vector2Int& operator /=(const Vector2Int& other);

		// Subscript operator
		int& operator [](int index) { return (Axis)index == Axis::X ? X : Y; }
		int operator [](int index) const { return (Axis)index == Axis::X ? X : Y; }
		int& operator [](Axis axis) { return axis == Axis::X ? X : Y; }
		int operator [](Axis axis) const { return axis == Axis::X ? X : Y; }

		operator Vector2() const { return Vector2((float)X, (float)Y); }
		//operator Vector3Int() const { return Vector3Int(X, Y, 0); };

		int X, Y;
	};

	static Vector2Int operator *(int scalar, const Vector2Int& vector) { return vector * scalar; }
}
