#pragma once

#include <glm/glm.hpp>

#include <Honey/Math/MathFunctions.h>

namespace Honey::Math {

	struct Vector3;

	struct Vector2 {

		Vector2(float value = 0.0f) : X(value), Y(value) {}
		Vector2(float x, float y) : X(x), Y(y) {}
		Vector2(const Vector3& vector);

		static const Vector2 Left;
		static const Vector2 Right;
		static const Vector2 Up;
		static const Vector2 Down;
		
		static const Vector2 Zero;
		static const Vector2 One;

		operator glm::vec2() const { return glm::vec2(X, Y); }
		operator Vector3() const;

		// Methods
		void Normalize();
		void Set(float x, float y);
		bool ExactlyEquals(const Vector2& other);
		bool EssentiallyEquals(const Vector2& other);

		// Const methods
		float GetMagnitude() const;
		float GetSquaredMagnitude() const;
		Vector2 Normalized() const;

		// Static Methods
		// TODO: Angle
		// TODO: Perpendicular
		// TODO: Reflect
		static float Dot(const Vector2& a, const Vector2& b);
		static float Distance(const Vector2& a, const Vector2& b);
		static float SquaredDistance(const Vector2& a, const Vector2& b);
		static Vector2 Max(const Vector2& a, const Vector2& b);
		static Vector2 Min(const Vector2& a, const Vector2& b);
		static Vector2 Scale(const Vector2& a, const Vector2& b);

		// Comparison operators
		bool operator ==(const Vector2& other) { return Mathf::ApproximatelyEquals(X,other.X) && Mathf::ApproximatelyEquals(Y, other.Y); }
		bool operator !=(const Vector2& other) { return !(*this == other); }

		// Arithmetic operators
		Vector2 operator +(const Vector2& other) const { return Vector2(X + other.X, Y + other.Y); }
		Vector2 operator -(const Vector2& other) const { return Vector2(X * other.X, Y - other.Y); }
		Vector2 operator *(float scalar) const { return Vector2(X * scalar, Y * scalar); }
		Vector2 operator /(float scalar) const { return Vector2(X / scalar, Y / scalar); }

		float X, Y;
	};

}