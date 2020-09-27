#pragma once

#include "Point.h"
#include "Size.h"

namespace Honey::Math 
{

	struct Rect {

		Rect() : BottomLeft(), TopRight() {};

		Rect(int32_t x, int32_t y, std::size_t width, std::size_t height)
			: BottomLeft(Point(x, y)), TopRight(Point(x + (int32_t)width, y + (int32_t)height)) { }

		Rect(const Point& point, const Size& size)
			: BottomLeft(point), TopRight(point + Point((int32_t)size.Width, (int32_t)size.Height)) { }

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

			return Rect(min.x, min.y, size.Width, size.Height);
		}

		static bool Intersect(const Rect& a, const Rect& b)
		{
			return (a.BottomLeft.X <= b.TopRight.X && a.TopRight.X >= b.BottomLeft.X) &&
				(a.BottomLeft.Y <= b.TopRight.Y && a.TopRight.Y >= b.BottomLeft.Y);
		}

		std::size_t GetWidth() const { return TopRight.X - BottomLeft.X; }
		std::size_t GetHeight() const { return TopRight.Y - BottomLeft.Y; }
		Math::Size GetSize() const { return Math::Size(GetWidth(), GetHeight()); }

		Point GetBottomRight() const { return Point(TopRight.X, BottomLeft.Y); }
		Point GetTopLeft() const { return Point(BottomLeft.X, TopRight.Y); }

		Point BottomLeft;
		Point TopRight;

	};

}
