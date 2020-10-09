#pragma once

#include <Honey/Math/Vector/Vector2Int.h>

namespace Honey::Math {

	/**
	 * @brief Represent a Point in a plane.
	*/
	struct Point {

		/**
		 * @brief Construct Point from a single value.
		 * @param value The value.
		*/
		constexpr Point(Int value = 0)
			: x(value), y(value) { }

		/**
		 * @brief Construct Point from a its spatial components.
		 * @param x X component.
		 * @param y Y component.
		*/
		constexpr Point(Int x, Int y)
			: x(x), y(y) { }

		/**
		 * @brief Construct Point from a Vector2Int.
		 * @param vector The vector.
		*/
		constexpr Point(const Vector2Int& vector)
			: x(vector.x), y(vector.y) {}

		Int x; /** @brief X component */
		Int y; /** @brief Y component */

		/**
		 * @brief Add two points.
		 * @param other The other point.
		 * @return The resulting point.
		*/
		Point operator +(const Point& other) const { return Point(x + other.x, y + other.y); }

		/**
		 * @brief Subtract two points together.
		 * @param other The other point.
		 * @return The resulting point.
		*/
		Point operator -(const Point& other) const { return Point(x - other.x, y - other.y); }

		/**
		 * @brief Add point to this.
		 * @param other The other point.
		 * @return Reference to the resulting point.
		*/
		Point& operator +=(const Point& other) { return (*this = *this + other); }

		/**
		 * @brief Subtract point from this.
		 * @param other The other point.
		 * @return Reference to the resulting point.
		*/
		Point& operator -=(const Point& other) { return (*this = *this - other); }

		/**
		 * @brief Convert Point to Vector2Int.
		*/
		explicit operator Vector2Int() const { return Vector2Int(x, y); }

	};
}
