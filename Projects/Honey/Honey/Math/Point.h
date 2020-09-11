#pragma once

#include <cstddef>
#include <Honey/Math/Vector/Vector2Int.h>

namespace Honey::Math {

	struct Point {

		constexpr Point(int32_t value = 0)
			: X(value), Y(value) { }

		constexpr Point(int32_t x, int32_t y)
			: X(x), Y(y) { }

		constexpr Point(const Vector2Int& vector)
			: X(vector.X), Y(vector.Y) {}

		int32_t X;
		int32_t Y;

		Point operator +(const Point& other) const { return Point(X + other.X, Y + other.Y); }
		Point operator -(const Point& other) const { return Point(X - other.X, Y - other.Y); }

		Point& operator +=(const Point& other) { return (*this = *this + other); }
		Point& operator -=(const Point& other) { return (*this = *this - other); }

		explicit operator Vector2Int() const { return Vector2Int(X, Y); }

	};
}
