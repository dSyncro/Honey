#pragma once

#include <Honey/Math/Vector/Vector3.h>
#include <Honey/Math/Vector/Vector4.h>

namespace Honey {

	struct Color {

		static const Color White;
		static const Color Black;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Magenta;
		static const Color Cyan;
		static const Color Transparent;

		constexpr Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f)
			: R(r), G(g), B(b), A(a) { }

		constexpr Color(const Math::Vector3& color)
			: R(color.X), G(color.Y), B(color.Z), A(1.0f) { }
		
		constexpr Color(const Math::Vector4& color)
			: R(color.X), G(color.Y), B(color.Z), A(color.W) { }

		Math::Vector3 ToRGB() const { return Math::Vector3(R, G, B); }

		operator Math::Vector4() const { return Math::Vector4(R, G, B, A); }

		Color operator +(const Color& other) { return Color(R + other.R, G + other.G, B + other.B, A + other.A); }
		Color operator -(const Color& other) { return Color(R - other.R, G - other.G, B - other.B, A - other.A); }
		Color operator *(const Color& other) { return Color(R * other.R, G * other.G, B * other.B, A * other.A); }
		Color operator /(const Color& other) { return Color(R / other.R, G / other.G, B / other.B, A / other.A); }

		Color& operator +=(const Color& other) { return *this = *this + other; }
		Color& operator -=(const Color& other) { return *this = *this - other; }
		Color& operator *=(const Color& other) { return *this = *this * other; }
		Color& operator /=(const Color& other) { return *this = *this / other; }

		float R, G, B, A;

	};

}
