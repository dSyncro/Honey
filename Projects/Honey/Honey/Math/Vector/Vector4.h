#pragma once

namespace Honey::Math {

	struct Vector2;
	struct Vector3;
	struct Matrix4x4;

	struct Vector4 {

		enum class Axis {
			X = 0,
			Y = 1,
			Z = 2,
			W = 3
		};

		// Constructors
		constexpr Vector4(float value = 0.0f) : X(value), Y(value), Z(value), W(value) {}
		constexpr Vector4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}

		explicit Vector4(const Vector2& vector);
		explicit Vector4(const Vector3& vector);
		explicit Vector4(const Vector3& vector, float w);

		// Shorthands
		static const Vector4 Zero;
		static const Vector4 One;

		static const Vector4 Infinity;
		static const Vector4 NegativeInfinity;

		// Conversion operators
		explicit operator Vector2() const;
		explicit operator Vector3() const;

		// Methods
		Vector4& Normalize();
		Vector4& Round();
		Vector4& Set(float x, float y, float z, float w);
		bool ExactlyEquals(const Vector4& other);
		bool EssentiallyEquals(const Vector4& other);

		// Const methods
		float GetMagnitude() const;
		float GetSquaredMagnitude() const;
		Vector4 Normalized() const;
		Vector4 Rounded() const;

		// Static Methods
		static float Dot(const Vector4& a, const Vector4& b);
		static float Distance(const Vector4& a, const Vector4& b);
		static float SquaredDistance(const Vector4& a, const Vector4& b);
		static Vector4 Abs(const Vector4& vector);
		static Vector4 Sign(const Vector4& vector);
		static Vector4 ClampMagnitude(const Vector4& vector, float magnitude);
		static Vector4 Max(const Vector4& a, const Vector4& b);
		static Vector4 Min(const Vector4& a, const Vector4& b);
		static Vector4 Scale(const Vector4& a, const Vector4& b);
		static Vector4 Project(const Vector4& vector, const Vector4& normal);
		static Vector4 Lerp(const Vector4& a, const Vector4& b, float t);
		static Vector4 LerpClamped(const Vector4& a, const Vector4& b, float t);
		static Vector4 MoveTowards(const Vector4& a, const Vector4& b, float distance);

		// Comparison operators
		bool operator ==(const Vector4& other);
		bool operator !=(const Vector4& other) { return !(*this == other); }

		// Arithmetic operators
		Vector4 operator +() const { return *this; }
		Vector4 operator -() const { return Vector4(-X, -Y, -Z, -W); }
		Vector4 operator +(const Vector4& other) const { return Vector4(X + other.X, Y + other.Y, Z + other.Z, W + other.W); }
		Vector4 operator -(const Vector4& other) const { return Vector4(X * other.X, Y - other.Y, Z - other.Z, W - other.W); }
		Vector4 operator *(float scalar) const { return Vector4(X * scalar, Y * scalar, Z * scalar, W * scalar); }
		Vector4 operator *(const Vector4& other) const { return Vector4(X * other.X, Y * other.Y, Z * other.Z, W * other.W); }
		Vector4 operator *(const Matrix4x4& matrix) const;
		Vector4 operator /(float scalar) const { return Vector4(X / scalar, Y / scalar, Z / scalar, W / scalar); }
		Vector4 operator /(const Vector4& other) const { return Vector4(X / other.X, Y / other.Y, Z / other.Z, W / other.W); }

		// Assignment operators
		Vector4& operator +=(const Vector4& other);
		Vector4& operator -=(const Vector4& other);
		Vector4& operator *=(float scalar);
		Vector4& operator *=(const Vector4& vector);
		Vector4& operator /=(float scalar);
		Vector4& operator /=(const Vector4& vector);

		// Subscript operator
		float operator [](int index);
		float operator [](int index) const;
		float operator [](Axis axis);
		float operator [](Axis axis) const;

		union {
			float X;
			float R;
		};
		union {
			float Y;
			float G;
		};
		union {
			float Z;
			float B;
		};
		union {
			float W;
			float A;
		};
	};

	static Vector4 operator *(float scalar, const Vector4& vector) { return vector * scalar; }

}
