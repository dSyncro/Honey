#pragma once

#include <cstddef>
#include <Honey/Math/Vector/Vector2Int.h>

namespace Honey::Math {

	/**
	 * @brief Structure representing a bidimensional size.
	*/
	struct Size {

		/**
		 * @brief Construct Size from a single value.
		 * @param value The value.
		*/
		constexpr Size(UInt value = 0)
			: width(value), height(value) { }

		/**
		 * @brief Construct Size from width and height.
		 * @param width The width.
		 * @param height The height.
		*/
		constexpr Size(UInt width, UInt height)
			: width(width), height(height) { }

		/**
		 * @brief Construct Size from a Vector2Int.
		 * @param vector The vector.
		*/
		constexpr Size(const Vector2Int& vector)
			: width(vector.x), height(vector.y) { }

		UInt width; /** @brief The width. */
		UInt height; /** @brief The height. */

		/**
		 * @brief Get area from size.
		 * @return The area.
		*/
		UInt getArea() const { return width * height; }

		/**
		 * @brief Convert Size to Vector2Int.
		*/
		explicit operator Vector2Int() const { return Vector2Int(static_cast<Int>(width), static_cast<Int>(height)); }
	};

}
