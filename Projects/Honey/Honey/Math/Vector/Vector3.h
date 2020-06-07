#pragma once

#include <glm/glm.hpp>

namespace Honey::Math {

	struct Vector2;
	struct Vector4;

	struct Vector3 {

		enum class Axis {
			X = 0,
			Y = 1,
			Z = 2
		};

		// Constructors
		Vector3(float value = 0.0f) : X(value), Y(value), Z(value) {}
		Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
		Vector3(const Vector2& vector);
		Vector3(const Vector4& vector);

		// Shorthands
		static const Vector3 Left;
		static const Vector3 Right;
		static const Vector3 Up;
		static const Vector3 Down;
		static const Vector3 Forward;
		static const Vector3 Back;

		static const Vector3 Zero;
		static const Vector3 One;
		
		static const Vector3 Infinity;
		static const Vector3 NegativeInfinity;

		// Conversion operators
		operator glm::vec3() const { return glm::vec3(X, Y, Z); }
		explicit operator Vector2() const;
		explicit operator Vector4() const;

		// Methods
		void Normalize();
		void Round();
		void Set(float x, float y, float z);
		bool ExactlyEquals(const Vector3& other);
		bool EssentiallyEquals(const Vector3& other);

		// Const methods
		float GetMagnitude() const;
		float GetSquaredMagnitude() const;
		Vector3 Normalized() const;
		Vector3 Rounded() const;

		// Static Methods
		static float Angle(const Vector3& a, const Vector3& b);
		static float Dot(const Vector3& a, const Vector3& b);
		static float Distance(const Vector3& a, const Vector3& b);
		static float SquaredDistance(const Vector3& a, const Vector3& b);
		static Vector3 Abs(const Vector3& vector);
		static Vector3 Sign(const Vector3& vector);
		static Vector3 ClampMagnitude(const Vector3& vector, float magnitude);
		static Vector3 Cross(const Vector3& a, const Vector3& b);
		static Vector3 Max(const Vector3& a, const Vector3& b);
		static Vector3 Min(const Vector3& a, const Vector3& b);
		static Vector3 Scale(const Vector3& a, const Vector3& b);
		static Vector3 Project(const Vector3& vector, const Vector3& normal);
		static Vector3 ProjectOnPlane(const Vector3& vector, const Vector3& planeNormal);
		static Vector3 Reflect(const Vector3& vector, const Vector3& normal);
		static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
		static Vector3 LerpClamped(const Vector3& a, const Vector3& b, float t);
		static Vector3 MoveTowards(const Vector3& a, const Vector3& b, float distance);

		// Comparison operators
		bool operator ==(const Vector3& other);
		bool operator !=(const Vector3& other) { return !(*this == other); }

		// Arithmetic operators
		Vector3 operator +() const { return *this; }
		Vector3 operator -() const { return Vector3(-X, -Y, -Z); }
		Vector3 operator +(const Vector3& other) const { return Vector3(X + other.X, Y + other.Y, Z + other.Z); }
		Vector3 operator -(const Vector3& other) const { return Vector3(X * other.X, Y - other.Y, Z - other.Z); }
		Vector3 operator *(float scalar) const { return Vector3(X * scalar, Y * scalar, Z * scalar); }
		Vector3 operator *(const Vector3& other) const { return Vector3(X * other.X, Y * other.Y, Z * other.Z); }
		Vector3 operator /(float scalar) const { return Vector3(X / scalar, Y / scalar, Z / scalar); }
		Vector3 operator /(const Vector3& other) const { return Vector3(X / other.X, Y / other.Y, Z / other.Z); }

		// Assignment operators
		Vector3& operator +=(const Vector3& other);
		Vector3& operator -=(const Vector3& other);
		Vector3& operator *=(float scalar);
		Vector3& operator *=(const Vector3& vector);
		Vector3& operator /=(float scalar);
		Vector3& operator /=(const Vector3& vector);

		// Subscript operator
		float operator [](int index);
		float operator [](int index) const;
		float operator [](Axis axis);
		float operator [](Axis axis) const;

		float X, Y, Z;
	};

	Vector3 operator *(float scalar, const Vector3& vector) { return vector * scalar; }

}