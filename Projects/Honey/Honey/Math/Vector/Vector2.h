#pragma once

#include <glm/glm.hpp>

#include <Honey/Math/MathFunctions.h>

namespace Honey::Math {

	struct Vector3;

	// 2-Components Vector of `float` type.
	struct Vector2 {

		// Axes of the Vector
		enum class Axis {
			X = 0,
			Y = 1
		};

		Vector2(float value = 0.0f) : X(value), Y(value) {}
		Vector2(float x, float y) : X(x), Y(y) {}
		Vector2(const Vector3& vector);

		static const Vector2 Left; // Vector2(-1.0f, 0.0f)
		static const Vector2 Right; // Vector2(1.0f, 0.0f)
		static const Vector2 Up; // Vector2(0.0f, 1.0f)
		static const Vector2 Down; // Vector2(0.0f, -1.0f)
		
		static const Vector2 Zero; // Vector2(0.0f, 0.0f)
		static const Vector2 One; // Vector2(1.0f, 1.0f)

		static const Vector2 Infinity; // Vector2(+Infinity, +Infinity)
		static const Vector2 NegativeInfinity; // Vector2(-Infinity, -Infinity)

		operator glm::vec2() const { return glm::vec2(X, Y); }
		operator Vector3() const;

		// Methods
		void Normalize();
		void Round();
		void Set(float x, float y);
		bool ExactlyEquals(const Vector2& other);
		bool EssentiallyEquals(const Vector2& other);

		// Const methods
		float GetMagnitude() const;
		float GetSquaredMagnitude() const;
		Vector2 Normalized() const;
		Vector2 Rounded() const;

		// Static Methods
		static float Angle(const Vector2& a, const Vector2& b);
		static float Dot(const Vector2& a, const Vector2& b);
		static float Distance(const Vector2& a, const Vector2& b);
		static float SquaredDistance(const Vector2& a, const Vector2& b);
		static Vector2 Abs(const Vector2& vector);
		static Vector2 Sign(const Vector2& vector);
		static Vector2 PerpendicularClockwise(const Vector2& vector);
		static Vector2 PerpendicularCounterClockwise(const Vector2& vector);
		static Vector2 ClampMagnitude(const Vector2& vector, float magnitude);
		static Vector2 Rotate(const Vector2& vector, float angle);
		static Vector2 Max(const Vector2& a, const Vector2& b);
		static Vector2 Min(const Vector2& a, const Vector2& b);
		static Vector2 Scale(const Vector2& a, const Vector2& b);
		static Vector2 Reflect(const Vector2& vector, const Vector2& normal);
		static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
		static Vector2 LerpClamped(const Vector2& a, const Vector2& b, float t);
		static Vector2 MoveTowards(const Vector2& a, const Vector2& b, float distance);

		// Comparison operators
		bool operator ==(const Vector2& other) { return Mathf::ApproximatelyEquals(X, other.X) && Mathf::ApproximatelyEquals(Y, other.Y); }
		bool operator !=(const Vector2& other) { return !(*this == other); }

		// Arithmetic operators
		Vector2 operator +() const { return *this; }
		Vector2 operator -() const { return Vector2(-X, -Y); }
		Vector2 operator +(const Vector2& other) const { return Vector2(X + other.X, Y + other.Y); }
		Vector2 operator -(const Vector2& other) const { return Vector2(X * other.X, Y - other.Y); }
		Vector2 operator *(float scalar) const { return Vector2(X * scalar, Y * scalar); }
		Vector2 operator *(const Vector2& other) const { return Vector2(X * other.X, Y * other.Y); }
		Vector2 operator /(float scalar) const { return Vector2(X / scalar, Y / scalar); }
		Vector2 operator /(const Vector2& other) const { return Vector2(X / other.X, Y / other.Y); }

		// Assignment operators
		Vector2& operator +=(const Vector2& other);
		Vector2& operator -=(const Vector2& other);
		Vector2& operator *=(float scalar);
		Vector2& operator *=(const Vector2& vector);
		Vector2& operator /=(float scalar);
		Vector2& operator /=(const Vector2& vector);

		// Subscript operator
		float operator [](int index) { return (Axis)index == Axis::X ? X : Y; }
		float operator [](int index) const { return (Axis)index == Axis::X ? X : Y; }
		float operator [](Axis axis) { return axis == Axis::X ? X : Y; }
		float operator [](Axis axis) const { return axis == Axis::X ? X : Y; }

		float X, Y;
	};

	Vector2 operator *(float scalar, const Vector2& vector) { return vector * scalar; }

}