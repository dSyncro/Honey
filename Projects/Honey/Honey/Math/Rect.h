#pragma once

#include "Point.h"
#include "Size.h"

namespace Honey::Math 
{

	struct Rect {

		constexpr Rect() : Location(), Dimensions() {};

		constexpr Rect(int32_t x, int32_t y, std::size_t width, std::size_t height)
			: Location(x, y), Dimensions(width, height) { }

		constexpr Rect(Point& point, Size& size)
			: Location(point), Dimensions(size) { }

		static Rect FromBounds(const Point& bottomLeft, const Point& topRight)
		{
			int32_t x = bottomLeft.X;
			int32_t y = bottomLeft.Y;
			std::size_t width = (int64_t)topRight.X - x;
			std::size_t height = (int64_t)topRight.Y - y;
			return Rect(x, y, width, height);
		}

		static Rect FromUnorderedBounds(const Point& a, const Point& b)
		{
			Vector2Int min = Vector2Int(Mathf::Min(a.X, b.X), Mathf::Min(a.Y, b.Y));
			Vector2Int max = Vector2Int(Mathf::Max(a.X, b.X), Mathf::Max(a.Y, b.Y));
			Size size = (Size)(max - min);

			return Rect(min.X, min.Y, size.Width, size.Height);
		}

		static bool Intersect(const Rect& a, const Rect& b)
		{
			return (a.X <= (b.X + b.Width) && (a.X + a.Width) >= b.X) &&
				(a.Y <= (b.Y + b.Height) && (a.Y + a.Height) >= b.Y);
		}

		union {
			struct {
				int32_t X;
				int32_t Y;
			};
			Point Location;
		};

		union {
			struct {
				std::size_t Width;
				std::size_t Height;
			};
			Size Dimensions;
		};

	};

}
