#pragma once

#include <cstdint>
#include <ostream>

namespace Honey
{
	/**
	 * @brief All possible mouse buttons.
	*/
	enum class MouseButton : UShort
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	};

	inline std::ostream& operator<<(std::ostream& os, MouseButton mouseCode)
	{
		os << static_cast<UShort>(mouseCode);
		return os;
	}
}

#define HNY_MOUSE_BUTTON_0      ::Honey::MouseButton::Button0
#define HNY_MOUSE_BUTTON_1      ::Honey::MouseButton::Button1
#define HNY_MOUSE_BUTTON_2      ::Honey::MouseButton::Button2
#define HNY_MOUSE_BUTTON_3      ::Honey::MouseButton::Button3
#define HNY_MOUSE_BUTTON_4      ::Honey::MouseButton::Button4
#define HNY_MOUSE_BUTTON_5      ::Honey::MouseButton::Button5
#define HNY_MOUSE_BUTTON_6      ::Honey::MouseButton::Button6
#define HNY_MOUSE_BUTTON_7      ::Honey::MouseButton::Button7
#define HNY_MOUSE_BUTTON_LAST   ::Honey::MouseButton::ButtonLast
#define HNY_MOUSE_BUTTON_LEFT   ::Honey::MouseButton::ButtonLeft
#define HNY_MOUSE_BUTTON_RIGHT  ::Honey::MouseButton::ButtonRight
#define HNY_MOUSE_BUTTON_MIDDLE ::Honey::MouseButton::ButtonMiddle
