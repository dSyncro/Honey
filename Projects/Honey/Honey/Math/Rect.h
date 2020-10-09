#pragma once

#include "Point.h"
#include "Size.h"

namespace Honey::Math 
{
	/**
	 * @brief Representation of a rectangle (AABB).
	*/
	struct Rect {

		/**
		 * @brief Construct a default rectangle.
		*/
		constexpr Rect() : bottomLeft(), topRight() {};

		/**
		 * @brief Construct a rectangle from its bottom left point and its dimensions.
		 * @param x X coordinate of the bottom left point.
		 * @param y Y coordinate of the bottom left point.
		 * @param width Width of the rectangle.
		 * @param height Height of the rectangle.
		*/
		constexpr Rect(Int x, Int y, UInt width, UInt height)
			: bottomLeft(Point(x, y)), topRight(Point(x + static_cast<Int>(width), y + static_cast<Int>(height))) { }

		/**
		 * @brief Construct a rectangle from its bottom left point and its dimensions.
		 * @param point Bottom left point.
		 * @param size Dimensions.
		*/
		Rect(const Point& point, const Size& size)
			: bottomLeft(point), topRight(point + Point(static_cast<Int>(size.width), static_cast<Int>(size.height))) { }

		/**
		 * @brief Create a rectangle from its bounds.
		 * @param bottomLeft Bottom left point.
		 * @param topRight Top right point.
		 * @return The rectangle defined by the specified bounds.
		*/
		static Rect fromBounds(const Point& bottomLeft, const Point& topRight)
		{
			Int x = bottomLeft.x;
			Int y = bottomLeft.y;
			UInt width = topRight.x - x;
			UInt height = topRight.y - y;
			return Rect(x, y, width, height);
		}

		/**
		 * @brief Create a rectangle from its bounds.
		 * Use this version when you don't know which bound is which.
		 * @param a First bound.
		 * @param b Second bound.
		 * @return The rectangle defined by the specified bounds.
		*/
		static Rect fromUnorderedBounds(const Point& a, const Point& b)
		{
			Vector2Int min = Vector2Int(Mathf::min(a.x, b.x), Mathf::min(a.y, b.y));
			Vector2Int max = Vector2Int(Mathf::max(a.x, b.x), Mathf::max(a.y, b.y));
			Size size = static_cast<Size>(max - min);

			return Rect(min.x, min.y, size.width, size.height);
		}

		/**
		 * @brief Check if two rectangle intersect.
		 * @param a First rectangle.
		 * @param b Second rectangle.
		*/
		static bool intersect(const Rect& a, const Rect& b)
		{
			return (a.bottomLeft.x <= b.topRight.x && a.topRight.x >= b.bottomLeft.x) &&
				(a.bottomLeft.y <= b.topRight.y && a.topRight.y >= b.bottomLeft.y);
		}

		/**
		 * @brief Get rectangle width.
		 * @return The width.
		*/
		UInt getWidth() const { return topRight.x - bottomLeft.x; }

		/**
		 * @brief Get rectangle height.
		 * @return The height.
		*/
		UInt getHeight() const { return topRight.y - bottomLeft.y; }

		/**
		 * @brief Get rectangle size.
		 * @return The size.
		*/
		Size getSize() const { return Size(getWidth(), getHeight()); }

		/**
		 * @brief Compute bottom right point of the rectangle.
		 * @return The bottom right point.
		*/
		Point getBottomRight() const { return Point(topRight.x, bottomLeft.y); }

		/**
		 * @brief Compute top left point of the rectangle.
		 * @return The top left point.
		*/
		Point getTopLeft() const { return Point(bottomLeft.x, topRight.y); }

		Point bottomLeft; /** @brief Bottom left point of the rectangle. */
		Point topRight; /** @brief Top right point of the rectangle. */

	};

}
