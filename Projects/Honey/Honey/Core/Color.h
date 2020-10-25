/**
 * @file Color.h
 * @brief Color API
*/

#pragma once

#include <Honey/Math/Vector/Vector3.h>
#include <Honey/Math/Vector/Vector4.h>

namespace Honey {

	/**
	 * @brief Common RGBA Color
	*/
	struct Color {

		static const Color& white(); /** @brief White Color */
		static const Color& black(); /** @brief Black Color */
		static const Color& red(); /** @brief Red Color*/
		static const Color& green(); /** @brief Green Color */
		static const Color& blue(); /** @brief Blue Color */
		static const Color& yellow(); /** @breif Yellow Color */
		static const Color& magenta(); /** @brief Magenta */
		static const Color& cyan(); /** @brief Cyan */
		static const Color& transparent(); /** @brief Transparent */

		/**
		 * @brief Create a color from its RGBA components.
		 * @param r -> Red Component.
		 * @param g -> Green Component.
		 * @param b -> Blue Component.
		 * @param a -> Alpha Component.
		*/
		constexpr Color(Float r = 0.0f, Float g = 0.0f, Float b = 0.0f, Float a = 1.0f)
			: r(r), g(g), b(b), a(a) { }

		/**
		 * @brief Create a color from a Vector3 representing a RGB color.
		 * @param color -> RGB color.
		*/
		constexpr Color(const Math::Vector3& color)
			: r(color.x), g(color.y), b(color.z), a(1.0f) { }
		
		/**
		 * @brief Create a color from a Vector4 representing a RGBA color.
		 * @param color -> RGBA color.
		*/
		constexpr Color(const Math::Vector4& color)
			: r(color.x), g(color.y), b(color.z), a(color.w) { }

		/**
		 * @brief Clamp exceeding components to one.
		 * @return A reference to the color itself.
		*/
		Color& clampToOne()
		{
			if (r > 1.0f) r = 1.0f;
			if (g > 1.0f) g = 1.0f;
			if (b > 1.0f) b = 1.0f;
			if (a > 1.0f) a = 1.0f;
			return *this;
		}

		/**
		 * @brief Convert Color to a RGB vector.
		 * @return A RGB color vector.
		*/
		Math::Vector3 toRGB() const { return Math::Vector3(r, g, b); }

		/**
		 * @brief Convert Color to a RGBA vector.
		 * @return A RGBA color vector.
		*/
		Math::Vector4 toRGBA() const { return Math::Vector4(r, g, b, a); }

		/**
		 * @brief Convert Color to Vector4.
		*/
		operator Math::Vector4() const { return toRGBA(); }

		/**
		 * @brief Add two colors.
		 * @param other -> The other Color.
		 * @return A Color made up of the sum of the two original colors.
		*/
		Color operator +(const Color& other) { return Color(r + other.r, g + other.g, b + other.b, a + other.a); }

		/**
		 * @brief Subtract a color by another.
		 * @param other -> The other Color.
		 * @return A Color made up of the difference of the two original colors.
		*/
		Color operator -(const Color& other) { return Color(r - other.r, g - other.g, b - other.b, a - other.a); }

		/**
		 * @brief Multiply two colors.
		 * @param other -> The other Color.
		 * @return The resulting Color.
		*/
		Color operator *(const Color& other) { return Color(r * other.r, g * other.g, b * other.b, a * other.a); }

		/**
		 * @brief Divide a color by another.
		 * @param other -> The other Color.
		 * @return The resulting Color.
		*/
		Color operator /(const Color& other) { return Color(r / other.r, g / other.g, b / other.b, a / other.a); }

		/**
		 * @brief Add color to this and return it.
		 * @param other -> Color to add.
		 * @return this Color.
		*/
		Color& operator +=(const Color& other) { return *this = *this + other; }

		/**
		 * @brief Subtract color to this and return it.
		 * @param other -> Color to subtract.
		 * @return this Color.
		*/
		Color& operator -=(const Color& other) { return *this = *this - other; }

		/**
		 * @brief Multiply this by color.
		 * @param other -> Color to multiply by.
		 * @return this Color.
		*/
		Color& operator *=(const Color& other) { return *this = *this * other; }

		/**
		 * @brief Divide this by color.
		 * @param other -> Color to divide by.
		 * @return this Color.
		*/
		Color& operator /=(const Color& other) { return *this = *this / other; }

		Float r; /** @brief Red Component */
		Float g; /** @brief Green Component */
		Float b; /** @brief Blue Component */
		Float a; /** @brief Alpha Component */

	};

}
