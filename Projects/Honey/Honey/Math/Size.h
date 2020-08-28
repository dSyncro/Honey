#pragma once

#include <cstddef>
#include <Honey/Math/Vector/Vector2Int.h>

namespace Honey::Math {

	struct Size {

		constexpr Size(std::size_t value = 0)
			: Width(value), Height(value) { }

		constexpr Size(std::size_t width, std::size_t height)
			: Width(width), Height(height) { }

		constexpr Size(const Vector2Int& vector)
			: Width(vector.X), Height(vector.Y) { }

		std::size_t Width;
		std::size_t Height;

		std::size_t GetArea() const { return Width * Height; }

		explicit operator Vector2Int() const { return Vector2Int((int)Width, (int)Height); }
	};

}
