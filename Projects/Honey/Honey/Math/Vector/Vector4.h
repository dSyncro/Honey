#pragma once

#include "Vector3.h"

namespace Honey::Math {

	struct Matrix4x4;

	/**
	 * @struct Vector3
	 * @brief 4-Components Vector of `float` type.
	*/
	struct Vector4 {

		enum class Axis {
			X = 0, /** @brief X axis. */
			Y = 1, /** @brief Y axis. */
			Z = 2, /** @brief Z axis. */
			W = 3  /** @brief W axis. */
		};

		// Constructors

		/**
		 * @brief Construct a Vector4 from a single value.
		 * All components will be initialized to it.
		 * @param value The value.
		*/
		constexpr Vector4(float value = 0.0f) : x(value), y(value), z(value), w(value) {}

		/**
		 * @brief Construct a Vector4 from its components.
		 * @param x X component.
		 * @param y Y component.
		 * @param z Z component.
		 * @param w W component.
		*/
		constexpr Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

		/**
		 * @brief Construct a Vector4 from a Vector2.
		 * @param vector The Vector2
		*/
		constexpr explicit Vector4(const Vector2& vector) : x(vector.x), y(vector.y), z(0.0f), w(0.0f) {}

		/**
		 * @brief Construct a Vector4 from a Vector3.
		 * @param vector The Vector3.
		*/
		constexpr explicit Vector4(const Vector3& vector) : x(vector.x), y(vector.y), z(vector.z), w(0.0f) {}

		/**
		 * @brief Construct a Vector4 from two Vector2.
		 * @param a First vector (x and y components).
		 * @param b Second vector (z and w components).
		*/
		constexpr explicit Vector4(const Vector2& a, const Vector2& b) : x(a.x), y(a.y), z(a.x), w(a.y) {}

		/**
		 * @brief Construct a Vector4 from a Vector3 and a fourth component.
		 * @param vector The Vector3.
		 * @param w The fourth component.
		*/
		constexpr explicit Vector4(const Vector3& vector, float w) : x(vector.x), y(vector.y), z(vector.z), w(w) {}

		// Shorthands

		/** @brief Vector4(0.0f) */
		static const Vector4& zero();

		/** @brief Vector4(1.0f) */
		static const Vector4& one();

		/** @brief Vector4(Infinity) */
		static const Vector4& infinity();

		/** @brief Vector4(-Infinity) */
		static const Vector4& negativeInfinity();

		// Conversion operators

		/**
		 * @brief Convert Vector4 to Vector2.
		*/
		explicit operator Vector2() const { return Vector2(x, y); }

		/**
		 * @brief Convert Vector4 to Vector3.
		*/
		explicit operator Vector3() const { return Vector3(x, y, z); }

		// Methods

		/**
		 * @brief Normalize this vector and return it.
		 * @return Normalized vector.
		*/
		Vector4& normalize();

		/**
		 * @brief Round this vector components and return it.
		 * @return Rounded vector.
		*/
		Vector4& round();

		/**
		 * @brief Set new components to vector.
		 * @param x X component.
		 * @param y Y component.
		 * @param z Z component.
		 * @param w W component.
		 * @return This vector with new values set.
		*/
		Vector4& set(float x, float y, float z, float w);

		/**
		 * @brief Check if two Vector4 are exactly the same.
		 * @param other The other vector.
		*/
		bool exactlyEquals(const Vector4& other);

		/**
		 * @brief Get if two Vector4 are essentially the same. (depends on float epsilon)
		 * @param other The other vector.
		*/
		bool essentiallyEquals(const Vector4& other);

		// Const methods

		/**
		 * @brief Get vector magnitude.
		 * @return The vector magnitude.
		*/
		float getMagnitude() const;

		/**
		 * @brief Get vector squared magnitude.
		 * @return The vector squared magnitude.
		*/
		float getSquaredMagnitude() const;

		/**
		 * @brief Get normalized version of this vector.
		 * @return Normalized vector.
		*/
		Vector4 normalized() const;

		/**
		 * @brief Get rounded version of this vector.
		 * @return Rounded-components vector.
		*/
		Vector4 rounded() const;

		// Static Methods

		/**
		 * @brief Get dot product of two Vector4.
		 * @param a First vector.
		 * @param b Second vector.
		 * @return The dot product.
		*/
		static float dot(const Vector4& a, const Vector4& b);

		/**
		 * @brief Get distance between two Vector4.
		 * @param a First vector.
		 * @param b Second vector.
		 * @return The distance.
		*/
		static float distance(const Vector4& a, const Vector4& b);

		/**
		 * @brief Get squared distance between two Vector4.
		 * @param a First vector.
		 * @param b Second vector.
		 * @return The squared distance.
		*/
		static float squaredDistance(const Vector4& a, const Vector4& b);

		/**
		 * @brief Get a vector made up of the absolute value of each component
		 * of the specified vector.
		 * @param vector The vector.
		 * @return Abs vector.
		*/
		static Vector4 abs(const Vector4& vector);

		/**
		 * @brief Get sign vector.
		 * @param vector The vector.
		 * @return Sign vector.
		 * @see Vector2::sign(const Vector2&);
		*/
		static Vector4 sign(const Vector4& vector);

		/**
		 * @brief Clamp specified vector to a certain magnitude.
		 * @param vector The vector.
		 * @param magnitude The magnitude.
		 * @return A new vector based on the one provided but with clamped magnitude.
		*/
		static Vector4 clampMagnitude(const Vector4& vector, float magnitude);

		/**
		 * @brief Get a vector made up of the maximum of each component
		 * of the two provided vectors.
		 * @param a First vector.
		 * @param b Second vector.
		 * @return The maximum vector.
		*/
		static Vector4 max(const Vector4& a, const Vector4& b);

		/**
		 * @brief Get a vector made up of the minimum of each component
		 * of the two provided vectors.
		 * @param a First vector.
		 * @param b Second vector.
		 * @return The minimum vector.
		*/
		static Vector4 min(const Vector4& a, const Vector4& b);

		/**
		 * @brief Scale a vector by another.
		 * @param a First vector.
		 * @param b Second vector.
		 * @return The scaled vector.
		*/
		static Vector4 scale(const Vector4& a, const Vector4& b);

		/**
		 * @brief Project vector on a normal.
		 * @param vector The vector to project.
		 * @param normal The normal.
		 * @return The projection of the vector on the normal.
		*/
		static Vector4 project(const Vector4& vector, const Vector4& normal);

		/**
		 * @brief Linear interpolate from a vector to another.
		 * @param a Departure vector. returned when t = 0.
		 * @param b Destination vector. returned when t = 1.
		 * @param t Interpolant.
		 * @return The interpolated vector.
		*/
		static Vector4 lerp(const Vector4& a, const Vector4& b, float t);

		/**
		 * @brief Linear interpolate from a vector to another.
		 * @param a Departure vector. returned when t = 0.
		 * @param b Destination vector. returned when t = 1.
		 * @param t Interpolant. Clamped to a maximum of 1.
		 * @return The interpolated vector.
		*/
		static Vector4 lerpClamped(const Vector4& a, const Vector4& b, float t);

		/**
		 * @brief Interpolate from a vector to another using distance.
		 * @param a Departure vector.
		 * @param b Destination vector.
		 * @param distance Interpolation distance.
		 * @return The interpolated vector.
		*/
		static Vector4 moveTowards(const Vector4& a, const Vector4& b, float distance);

		// Comparison operators

		/**
		 * @brief Check if vector is equal to another.
		 * @param other The other vector.
		*/
		bool operator ==(const Vector4& other);

		/**
		 * @brief Check if vector differs from another.
		 * @param other The other vector.
		*/
		bool operator !=(const Vector4& other) { return !(*this == other); }

		// Arithmetic operators

		/**
		 * @brief Get this vector with inverted sign.
		*/
		Vector4 operator -() const { return Vector4(-x, -y, -z, -w); }

		/**
		 * @brief Sum two vectors.
		 * @param other The other vector.
		 * @return The resulting vector.
		*/
		Vector4 operator +(const Vector4& other) const { return Vector4(x + other.x, y + other.y, z + other.z, w + other.w); }

		/**
		 * @brief Subtract two vectors.
		 * @param other The vector to subtract.
		 * @return The resulting vector.
		*/
		Vector4 operator -(const Vector4& other) const { return Vector4(x * other.x, y - other.y, z - other.z, w - other.w); }

		/**
		 * @brief Multiply a vector by a scalar.
		 * @param scalar The scalar.
		 * @return The resulting vector.
		*/
		Vector4 operator *(float scalar) const { return Vector4(x * scalar, y * scalar, z * scalar, w * scalar); }

		/**
		 * @brief Multiply a vector by another.
		 * @param other The other vector.
		 * @return The resulting vector.
		*/
		Vector4 operator *(const Vector4& other) const { return Vector4(x * other.x, y * other.y, z * other.z, w * other.w); }

		/**
		 * @brief Multiply a vector by a Matrix4x4 (usually a TRS matrix).
		 * @param matrix The matrix.
		 * @return The resulting vector.
		*/
		Vector4 operator *(const Matrix4x4& matrix) const;

		/**
		 * @brief Divide a vector by a scalar.
		 * @param scalar The scalar.
		 * @return The resulting vector.
		*/
		Vector4 operator /(float scalar) const { return Vector4(x / scalar, y / scalar, z / scalar, w / scalar); }

		/**
		 * @brief Divide a vector by another.
		 * @param other The other vector.
		 * @return The resulting vector.
		*/
		Vector4 operator /(const Vector4& other) const { return Vector4(x / other.x, y / other.y, z / other.z, w / other.w); }

		// Assignment operators

		/**
		 * @brief Add vector to this.
		 * @param other The other vector.
		*/
		Vector4& operator +=(const Vector4& other);

		/**
		 * @brief Subtract vector from this.
		 * @param other The other vector.
		*/
		Vector4& operator -=(const Vector4& other);

		/**
		 * @brief Multiply this by a scalar.
		 * @param scalar The scalar.
		*/
		Vector4& operator *=(float scalar);

		/**
		 * @brief Multiply this by a vector.
		 * @param other The other vector.
		*/
		Vector4& operator *=(const Vector4& vector);

		/**
		 * @brief Divide this by a scalar.
		 * @param scalar The scalar.
		*/
		Vector4& operator /=(float scalar);

		/**
		 * @brief Divide this by a vector.
		 * @param other The other vector.
		*/
		Vector4& operator /=(const Vector4& vector);

		// Subscript operator

		/**
		 * @brief Get component by index.
		 * @param index Index of component.
		 * @return Component at index. (returns last component if overflown)
		*/
		float& operator [](int index);

		/**
		 * @brief Get component by index. (const version)
		 * @param index Index of component.
		 * @return Component at index. (returns last component if overflown)
		*/
		float operator [](int index) const;

		/**
		 * @brief Get component by axis.
		 * @param axis component Axis.
		 * @return Component at axis.
		*/
		float& operator [](Axis axis);

		/**
		 * @brief Get component by axis. (const version)
		 * @param axis component Axis.
		 * @return Component at axis.
		*/
		float operator [](Axis axis) const;

		float x; /** @brief X component. */
		float y; /** @brief Y component. */
		float z; /** @brief Z component. */
		float w; /** @brief W component. */
	};


	/**
	 * @brief Multiply a scalar by a vector.
	 * @param scalar The scalar.
	 * @param vector The vector.
	 * @return The resulting vector.
	*/
	static Vector4 operator *(float scalar, const Vector4& vector) { return vector * scalar; }

}
