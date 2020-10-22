#pragma once

#include "Vector2.h"

namespace Honey::Math {

	/**
	 * @struct Vector2Int
	 * @brief 2-Components Vector of `int` type.
	*/
	struct Vector2Int {

		/** @brief Axes of the vector. */
		enum class Axis : Byte {
			X = 0, /** @brief X-axis. */
			Y = 1 /** @brief Y-axis. */
		};

		/**
		 * @brief Construct Vector2Int from single value.
		 * All components will be initialized to value.
		 * @param value The value.
		*/
		constexpr Vector2Int(Int value = 0) : x(value), y(value) {}

		/**
		 * @brief Construct Vector2Int from its components.
		 * @param x X component.
		 * @param y Y component.
		*/
		constexpr Vector2Int(Int x, Int y) : x(x), y(y) {}

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

		/**
		 * @brief Set vector components.
		 * @param x New X component.
		 * @param y New Y component.
		 * @return A reference to the vector.
		*/
		Vector2Int& set(Int x, Int y);

		/**
		 * @brief Clamp vector.
		 * @param min Min vector.
		 * @param max Max vector.
		 * @return A reference to the vector.
		*/
		Vector2Int& clamp(const Vector2Int& min, const Vector2Int& max);

		/**
		 * @brief Check if two Vector2Int are equal to each other.
		 * @param other The other vector.
		*/
		bool equals(const Vector2Int& other) const;

		/**
		 * @brief Get vector magnitude.
		 * @return The magnitude.
		*/
		Float getMagnitude() const;

		/**
		 * @brief Get vector magnitude squared.
		 * @return The squared magnitude.
		*/
		Int getSquaredMagnitude() const;

		/**
		 * @brief Get a vector made up of the absolute value
		 * of each component of another specified vector.
		 * @param vector The vector.
		 * @return A vector with positive values.
		*/
		static Vector2Int abs(const Vector2Int& vector);

		/**
		 * @brief Get sign vector of another specified vector.
		 * Given a vector, we refer as sign vector to the vector
		 * that holds the sign of each component (either -1 or 1).
		 * @param vector The vector.
		 * @return The sign vector.
		*/
		static Vector2Int sign(const Vector2Int& vector);

		/**
		 * @brief Convert a Vector2 to a Vector2Int ceiling each component.
		 * @param vector The Vector2.
		 * @return Ceiled vector.
		*/
		static Vector2Int ceilToInt(const Vector2& vector);

		/**
		 * @brief Convert a Vector2 to a Vector2Int flooring each component.
		 * @param vector The Vector2.
		 * @return Floored vector.
		*/
		static Vector2Int floorToInt(const Vector2& vector);

		/**
		 * @brief Convert a Vector2 to a Vector2Int rounding each component.
		 * @param vector The Vector2.
		 * @return Rounded vector.
		*/
		static Vector2Int roundToInt(const Vector2& vector);

		/**
		 * @brief Get a vector made up of the maximum components
		 * of the two provided vectors.
		 * @param a First vector.
		 * @param b Second vector.
		 * @return Maximum vector.
		*/
		static Vector2Int max(const Vector2Int& a, const Vector2Int& b);

		/**
		 * @brief Get a vector made up of the minimum components
		 * of the two provided vectors.
		 * @param a First vector.
		 * @param b Second vector.
		 * @return Minimum vector.
		*/
		static Vector2Int min(const Vector2Int& a, const Vector2Int& b);

		/**
		 * @brief Scale vector by another.
		 * @param a First vector.
		 * @param b Second vector.
		 * @return Scaled vector.
		*/
		static Vector2Int scale(const Vector2Int& a, const Vector2Int& b);

		/**
		 * @brief Get distance between two vectors.
		 * @param a First vector.
		 * @param b Second vector.
		 * @return Distance between two vectors.
		*/
		static Float distance(const Vector2Int& a, const Vector2Int& b);

		/**
		 * @brief Get squared distance between two vectors.
		 * @param a First vector.
		 * @param b Second vector.
		 * @return Squared distance between two vectors.
		*/
		static Int squaredDistance(const Vector2Int& a, const Vector2Int& b);

		/**
		 * @brief Check if two Vector2Int are equal to each other.
		 * @param other The other vector.
		*/
		bool operator ==(const Vector2Int& other) const { return x == other.x && y == other.y; }

		/**
		 * @brief Check if two Vector2Int differs from each other.
		 * @param other The other vector.
		*/
		bool operator !=(const Vector2Int& other) const { return !(*this == other); }

		/**
		 * @brief Get opposite vector.
		 * @return A vector with changed sign components.
		*/
		Vector2Int operator -() const { return Vector2Int(-x, -y); }

		/**
		 * @brief Add two Vector2Int.
		 * @param other The other vector.
		*/
		Vector2Int operator +(const Vector2Int& other) const { return Vector2Int(x + other.x, y + other.y); }

		/**
		 * @brief Subtract from Vector2Int.
		 * @param other The other vector.
		*/
		Vector2Int operator -(const Vector2Int& other) const { return Vector2Int(x - other.x, y - other.y); }

		/**
		 * @brief Multiply Vector2Int by scalar.
		 * @param scalar The scalar.
		*/
		Vector2Int operator *(Int scalar) const { return Vector2Int(x * scalar, y * scalar); }

		/**
		 * @brief Multiply two Vector2Int.
		 * @param other The other vector.
		*/
		Vector2Int operator *(const Vector2Int& other) const { return Vector2Int(x * other.x, y * other.y); }

		/**
		 * @brief Divide Vector2Int by scalar.
		 * @param scalar The scalar.
		*/
		Vector2Int operator /(Int scalar) const { return Vector2Int(x / scalar, y / scalar); }

		/**
		 * @brief Divide Vector2Int by another.
		 * @param other The other vector.
		*/
		Vector2Int operator /(const Vector2Int& other) const { return Vector2Int(x / other.x, y / other.y); }

		// Assignment operators

		/** @brief Add Vector2Int to self. */
		Vector2Int& operator +=(const Vector2Int& other);

		/** @brief Subtract Vector2Int to self. */
		Vector2Int& operator -=(const Vector2Int& other);

		/** @brief Multiply self by scalar. */
		Vector2Int& operator *=(int scalar);

		/** @brief Multiply Vector2Int by self. */
		Vector2Int& operator *=(const Vector2Int& other);

		/** @brief Divide self by scalar. */
		Vector2Int& operator /=(Int scalar);

		/** @brief Divide self by Vector2Int. */
		Vector2Int& operator /=(const Vector2Int& other);

		// Subscript operator

		/**
		 * @brief Get component by its index.
		 * Overflowing the maximum index will return the last component.
		 * @param index Component index.
		 * @return A reference to component.
		*/
		Int& operator [](Int index) { return static_cast<Axis>(index) == Axis::X ? x : y; }

		/**
		 * @brief Get component by its index.
		 * Overflowing the maximum index will return the last component.
		 * @param index Component index.
		 * @return A copy of the component.
		*/
		Int operator [](Int index) const { return static_cast<Axis>(index) == Axis::X ? x : y; }

		/**
		 * @brief Get component by its axis.
		 * @param axis Component axis.
		 * @return A reference to component.
		*/
		Int& operator [](Axis axis) { return axis == Axis::X ? x : y; }

		/**
		 * @brief Get component by its axis.
		 * @param axis Component axis.
		 * @return A copy of the component.
		*/
		Int operator [](Axis axis) const { return axis == Axis::X ? x : y; }

		/**
		 * @brief Convert Vector2Int to Vector2.
		*/
		operator Vector2() const { return Vector2(static_cast<Float>(x), static_cast<Float>(y)); }
		//operator Vector3Int() const { return Vector3Int(X, Y, 0); };

		Int x; /** @brief X component. */
		Int y; /** @brief Y component. */
	};

	static Vector2Int operator *(Int scalar, const Vector2Int& vector) { return vector * scalar; }
}
