#pragma once

#include "Vector2.h"

namespace Honey::Math {

	struct Matrix4x4;

	/**
	 * @struct Vector3
	 * @brief 3-Components Vector of `float` type.
	*/
	struct Vector3 {

		/** @brief Axes of the vector. */
		enum class Axis {
			X = 0, /** @brief X axis. */
			Y = 1, /** @brief Y axis. */
			Z = 2  /** @brief Z axis. */
		};

		// Constructors

		/**
		 * @brief Construct Vector3 from a single value.
		 * All components will be initialized to value.
		 * @param value The value.
		*/
		constexpr Vector3(float value = 0.0f) : x(value), y(value), z(value) {}

		/**
		 * @brief Construct Vector3 from its components.
		 * @param x X component.
		 * @param y Y component.
		 * @param z Z component.
		*/
		constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

		/**
		 * @brief Construct Vector3 from a Vector2.
		 * @param vector The Vector2.
		*/
		explicit Vector3(const Vector2& vector);

		/**
		 * @brief Construct a Vector3 from a Vector2 and a third component.
		 * @param vector The Vector2.
		 * @param z The third component.
		*/
		explicit Vector3(const Vector2& vector, float z);

		// Shorthands

		/** @brief Vector3(-1.0f,  0.0f,  0.0f) */
		static const Vector3& left();

		/** @brief Vector3(1.0f, 0.0f, 0.0f) */
		static const Vector3& right();

		/** @brief Vector3(0.0f, 1.0f, 0.0f) */
		static const Vector3& up();

		/** @brief Vector3(0.0f, -1.0f, 0.0f) */
		static const Vector3& down();

		/** @brief Vector3(0.0f, 0.0f, 1.0f) */
		static const Vector3& forward();

		/** @brief Vector3(0.0f, 0.0f, -1.0f) */
		static const Vector3& back();

		/** @brief Vector3(0.0f, 0.0f, 0.0f) */
		static const Vector3& zero();

		/** @brief Vector3(1.0f, 1.0f, 1.0f) */
		static const Vector3& one();

		/** @brief Vector3(Infinity, Infinity, Infinity) */
		static const Vector3& infinity();

		/** @brief Vector3(-Infinity, -Infinity, -Infinity) */
		static const Vector3& negativeInfinity();

		// Conversion operators

		/**
		 * @brief Convert to Vector2.
		*/
		explicit operator Vector2() const { return Vector2(x, y); }

		// Methods

		/**
		 * @brief Normalize this vector and return it.
		 * A normalized vector is a vector of magnitude equal to 1.
		 * @return A reference to the normalized vector.
		*/
		Vector3& normalize();

		/**
		 * @brief Round components of this vector and return it.
		 * @return A reference to the rounded vector.
		*/
		Vector3& round();

		/**
		 * @brief Set new components to vector and return it.
		 * @param x New X component.
		 * @param y New Y component.
		 * @param z New Z component.
		 * @return A reference to this vector.
		*/
		Vector3& set(float x, float y, float z);

		/**
		 * @brief Check if two vectors are exactly equal to each other.
		 * @param other The other vector.
		*/
		bool exactlyEquals(const Vector3& other);

		/**
		 * @brief Check if two vector are essentially equal to each other (depends on float epsilon).
		 * @param other The other vector.
		*/
		bool essentiallyEquals(const Vector3& other);

		// Const methods

		/**
		 * @brief Get vector magnitude.
		 * @return The magnitude.
		*/
		float getMagnitude() const;

		/**
		 * @brief Get vector squared magnitude.
		 * @return The squared magnitude.
		*/
		float getSquaredMagnitude() const;

		/**
		 * @brief Get normalized form of this vector.
		 * @return The normalized vector.
		*/
		Vector3 normalized() const;

		/**
		 * @brief Get rounded form of this vector.
		 * @return The rounded vector.
		*/
		Vector3 rounded() const;

		/**
		 * @brief Stringify vector.
		*/
		std::string toString() const;

		// Static Methods

		/**
		 * @brief Get angle between two vectors (in radians).
		 * @param a First vector.
		 * @param b Second vector.
		 * @return Angle in radians between the vectors.
		*/
		static float angle(const Vector3& a, const Vector3& b);

		/**
		 * @brief Get dot product of two vectors.
		 * @param a First vector.
		 * @param b Second vector.
		 * @return The dot product.
		*/
		static float dot(const Vector3& a, const Vector3& b);

		/**
		 * @brief Get distance between two vectors.
		 * @param a First vector.
		 * @param b Second vector.
		 * @return The distance between the vectors.
		*/
		static float distance(const Vector3& a, const Vector3& b);

		/**
		 * @brief Get squared distance between two vectors.
		 * @param a First vector.
		 * @param b Second vector.
		 * @return The squared distance between the vectors.
		*/
		static float squaredDistance(const Vector3& a, const Vector3& b);

		/**
		 * @brief Get a vector made up of the absolute value of each component
		 * of the specified vector.
		 * @param vector The vector.
		 * @return Abs vector.
		*/
		static Vector3 abs(const Vector3& vector);

		/**
		 * @brief Get sign vector.
		 * @param vector The vector.
		 * @return Sign vector.
		 * @see Vector2::sign(const Vector2&);
		*/
		static Vector3 sign(const Vector3& vector);

		/**
		 * @brief Clamp specified vector to a certain magnitude.
		 * @param vector The vector.
		 * @param magnitude The magnitude.
		 * @return A new vector based on the one provided but with clamped magnitude.
		*/
		static Vector3 clampMagnitude(const Vector3& vector, float magnitude);

		/**
		 * @brief Get cross product of two vectors.
		 * @param a First vector.
		 * @param b Second vector.
		 * @return The cross product.
		*/
		static Vector3 cross(const Vector3& a, const Vector3& b);

		/**
		 * @brief Get a vector made up of the maximum of each component 
		 * of the two provided vectors.
		 * @param a First vector.
		 * @param b Second vector.
		 * @return The maximum vector.
		*/
		static Vector3 max(const Vector3& a, const Vector3& b);

		/**
		 * @brief Get a vector made up of the minimum of each component 
		 * of the two provided vectors.
		 * @param a First vector.
		 * @param b Second vector.
		 * @return The minimum vector.
		*/
		static Vector3 min(const Vector3& a, const Vector3& b);

		/**
		 * @brief Scale a vector by another.
		 * @param a First vector.
		 * @param b Second vector.
		 * @return The scaled vector.
		*/
		static Vector3 scale(const Vector3& a, const Vector3& b);

		/**
		 * @brief Project vector on a normal.
		 * @param vector The vector to project.
		 * @param normal The normal.
		 * @return The projection of the vector on the normal.
		*/
		static Vector3 project(const Vector3& vector, const Vector3& normal);

		/**
		 * @brief Project vector on a plane.
		 * @param vector The vector to project.
		 * @param planeNormal The normal of the plane.
		 * @return The projection of the vector on the plane.
		*/
		static Vector3 projectOnPlane(const Vector3& vector, const Vector3& planeNormal);

		/**
		 * @brief Reflect vector on normal axis.
		 * @param vector The vector.
		 * @param normal The normal axis.
		 * @return The reflected vector.
		*/
		static Vector3 reflect(const Vector3& vector, const Vector3& normal);

		/**
		 * @brief Linear interpolate from a vector to another.
		 * @param a Departure vector. returned when t = 0.
		 * @param b Destination vector. returned when t = 1.
		 * @param t Interpolant.
		 * @return The interpolated vector.
		*/
		static Vector3 lerp(const Vector3& a, const Vector3& b, float t);

		/**
		 * @brief Linear interpolate from a vector to another.
		 * @param a Departure vector. returned when t = 0.
		 * @param b Destination vector. returned when t = 1.
		 * @param t Interpolant. Clamped to a maximum of 1.
		 * @return The interpolated vector.
		*/
		static Vector3 lerpClamped(const Vector3& a, const Vector3& b, float t);

		/**
		 * @brief Interpolate from a vector to another using distance.
		 * @param a Departure vector.
		 * @param b Destination vector.
		 * @param distance Interpolation distance.
		 * @return The interpolated vector.
		*/
		static Vector3 moveTowards(const Vector3& a, const Vector3& b, float distance);

		// Comparison operators

		/**
		 * @brief Check if vector is equal to another.
		 * @param other The other vector.
		*/
		bool operator ==(const Vector3& other);

		/**
		 * @brief Check if vector differs from another.
		 * @param other The other vector.
		*/
		bool operator !=(const Vector3& other) { return !(*this == other); }

		// Arithmetic operators

		/**
		 * @brief Get this vector with inverted sign.
		*/
		Vector3 operator -() const { return Vector3(-x, -y, -z); }

		/**
		 * @brief Sum two vectors.
		 * @param other The other vector.
		 * @return The resulting vector.
		*/
		Vector3 operator +(const Vector3& other) const { return Vector3(x + other.x, y + other.y, z + other.z); }

		/**
		 * @brief Subtract two vectors.
		 * @param other The vector to subtract.
		 * @return The resulting vector.
		*/
		Vector3 operator -(const Vector3& other) const { return Vector3(x * other.x, y - other.y, z - other.z); }

		/**
		 * @brief Multiply a vector by a scalar.
		 * @param scalar The scalar.
		 * @return The resulting vector.
		*/
		Vector3 operator *(float scalar) const { return Vector3(x * scalar, y * scalar, z * scalar); }

		/**
		 * @brief Multiply a vector by another.
		 * @param other The other vector.
		 * @return The resulting vector.
		*/
		Vector3 operator *(const Vector3& other) const { return Vector3(x * other.x, y * other.y, z * other.z); }

		/**
		 * @brief Multiply a vector by a Matrix4x4 (usually a TRS matrix).
		 * @param matrix The matrix.
		 * @return The resulting vector.
		*/
		Vector3 operator *(const Matrix4x4& matrix) const;

		/**
		 * @brief Divide a vector by a scalar.
		 * @param scalar The scalar.
		 * @return The resulting vector.
		*/
		Vector3 operator /(float scalar) const { return Vector3(x / scalar, y / scalar, z / scalar); }

		/**
		 * @brief Divide a vector by another.
		 * @param other The other vector.
		 * @return The resulting vector.
		*/
		Vector3 operator /(const Vector3& other) const { return Vector3(x / other.x, y / other.y, z / other.z); }

		// Assignment operators

		/**
		 * @brief Add vector to this.
		 * @param other The other vector.
		*/
		Vector3& operator +=(const Vector3& other);

		/**
		 * @brief Subtract vector from this.
		 * @param other The other vector.
		*/
		Vector3& operator -=(const Vector3& other);

		/**
		 * @brief Multiply this by a scalar.
		 * @param scalar The scalar.
		*/
		Vector3& operator *=(float scalar);

		/**
		 * @brief Multiply this by a vector.
		 * @param other The other vector.
		*/
		Vector3& operator *=(const Vector3& vector);

		/**
		 * @brief Divide this by a scalar.
		 * @param scalar The scalar.
		*/
		Vector3& operator /=(float scalar);

		/**
		 * @brief Divide this by a vector.
		 * @param other The other vector.
		*/
		Vector3& operator /=(const Vector3& vector);

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
	};

	/**
	 * @brief Multiply a scalar by a vector.
	 * @param scalar The scalar.
	 * @param vector The vector.
	 * @return The resulting vector.
	*/
	static Vector3 operator *(float scalar, const Vector3& vector) { return vector * scalar; }

}
