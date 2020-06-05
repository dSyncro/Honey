#pragma once

#include <glm/glm.hpp>

#include <Honey/Math/MathFunctions.h>

namespace Honey::Math {

	struct Vector2;

	struct Vector3 {

		Vector3(float value = 0.0f) : X(value), Y(value), Z(value) {}
		Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
		Vector3(const Vector2& vector);

		static const Vector3 Left;
		static const Vector3 Right;
		static const Vector3 Up;
		static const Vector3 Down;
		static const Vector3 Forward;
		static const Vector3 Back;

		static const Vector3 Zero;
		static const Vector3 One;

		operator glm::vec3() const { return glm::vec3(X, Y, Z); }
		operator Vector2() const;

		// Methods
		void Normalize();
		void Set(float x, float y, float z);
		bool ExactlyEquals(const Vector3& other);
		bool EssentiallyEquals(const Vector3& other);

		// Const methods
		float GetMagnitude() const;
		float GetSquaredMagnitude() const;
		Vector3 Normalized() const;

		// Static Methods
		// TODO: Angle
		// TODO: Reflect
		static float Dot(const Vector3& a, const Vector3& b);
		static float Distance(const Vector3& a, const Vector3& b);
		static float SquaredDistance(const Vector3& a, const Vector3& b);
		static Vector3 Cross(const Vector3& a, const Vector3& b);
		static Vector3 Max(const Vector3& a, const Vector3& b);
		static Vector3 Min(const Vector3& a, const Vector3& b);
		static Vector3 Scale(const Vector3& a, const Vector3& b);

		// Comparison operators
		bool operator ==(const Vector3& other) 
		{ 
			return Mathf::ApproximatelyEquals(X, other.X) 
				&& Mathf::ApproximatelyEquals(Y, other.Y)
				&& Mathf::ApproximatelyEquals(Z, other.Z); 
		}

		bool operator !=(const Vector3& other) { return !(*this == other); }

		// Arithmetic operators
		Vector3 operator +(const Vector3& other) const { return Vector3(X + other.X, Y + other.Y, Z + other.Z); }
		Vector3 operator -(const Vector3& other) const { return Vector3(X * other.X, Y - other.Y, Z - other.Z); }
		Vector3 operator *(float scalar) const { return Vector3(X * scalar, Y * scalar, Z * scalar); }
		Vector3 operator /(float scalar) const { return Vector3(X / scalar, Y / scalar, Z / scalar); }

		float X, Y, Z;
	};

}