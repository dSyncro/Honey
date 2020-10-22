#pragma once

#include <cstdint>
#include <ostream>

namespace Honey {

	/**
	 * @brief All possible keycodes.
	*/
	enum class Keycode : UShort
	{
		// From glfw3.h

		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	};

	inline std::ostream& operator<<(std::ostream& os, Keycode keyCode)
	{
		os << static_cast<UShort>(keyCode);
		return os;
	}
}

// From glfw3.h
#define HNY_KEY_SPACE           ::Honey::Keycode::Space
#define HNY_KEY_APOSTROPHE      ::Honey::Keycode::Apostrophe    /* ' */
#define HNY_KEY_COMMA           ::Honey::Keycode::Comma         /* , */
#define HNY_KEY_MINUS           ::Honey::Keycode::Minus         /* - */
#define HNY_KEY_PERIOD          ::Honey::Keycode::Period        /* . */
#define HNY_KEY_SLASH           ::Honey::Keycode::Slash         /* / */
#define HNY_KEY_0               ::Honey::Keycode::D0
#define HNY_KEY_1               ::Honey::Keycode::D1
#define HNY_KEY_2               ::Honey::Keycode::D2
#define HNY_KEY_3               ::Honey::Keycode::D3
#define HNY_KEY_4               ::Honey::Keycode::D4
#define HNY_KEY_5               ::Honey::Keycode::D5
#define HNY_KEY_6               ::Honey::Keycode::D6
#define HNY_KEY_7               ::Honey::Keycode::D7
#define HNY_KEY_8               ::Honey::Keycode::D8
#define HNY_KEY_9               ::Honey::Keycode::D9
#define HNY_KEY_SEMICOLON       ::Honey::Keycode::Semicolon     /* ; */
#define HNY_KEY_EQUAL           ::Honey::Keycode::Equal         /* = */
#define HNY_KEY_A               ::Honey::Keycode::A
#define HNY_KEY_B               ::Honey::Keycode::B
#define HNY_KEY_C               ::Honey::Keycode::C
#define HNY_KEY_D               ::Honey::Keycode::D
#define HNY_KEY_E               ::Honey::Keycode::E
#define HNY_KEY_F               ::Honey::Keycode::F
#define HNY_KEY_G               ::Honey::Keycode::G
#define HNY_KEY_H               ::Honey::Keycode::H
#define HNY_KEY_I               ::Honey::Keycode::I
#define HNY_KEY_J               ::Honey::Keycode::J
#define HNY_KEY_K               ::Honey::Keycode::K
#define HNY_KEY_L               ::Honey::Keycode::L
#define HNY_KEY_M               ::Honey::Keycode::M
#define HNY_KEY_N               ::Honey::Keycode::N
#define HNY_KEY_O               ::Honey::Keycode::O
#define HNY_KEY_P               ::Honey::Keycode::P
#define HNY_KEY_Q               ::Honey::Keycode::Q
#define HNY_KEY_R               ::Honey::Keycode::R
#define HNY_KEY_S               ::Honey::Keycode::S
#define HNY_KEY_T               ::Honey::Keycode::T
#define HNY_KEY_U               ::Honey::Keycode::U
#define HNY_KEY_V               ::Honey::Keycode::V
#define HNY_KEY_W               ::Honey::Keycode::W
#define HNY_KEY_X               ::Honey::Keycode::X
#define HNY_KEY_Y               ::Honey::Keycode::Y
#define HNY_KEY_Z               ::Honey::Keycode::Z
#define HNY_KEY_LEFT_BRACKET    ::Honey::Keycode::LeftBracket   /* [ */
#define HNY_KEY_BACKSLASH       ::Honey::Keycode::Backslash     /* \ */
#define HNY_KEY_RIGHT_BRACKET   ::Honey::Keycode::RightBracket  /* ] */
#define HNY_KEY_GRAVE_ACCENT    ::Honey::Keycode::GraveAccent   /* ` */
#define HNY_KEY_WORLD_1         ::Honey::Keycode::World1        /* non-US #1 */
#define HNY_KEY_WORLD_2         ::Honey::Keycode::World2        /* non-US #2 */

/* Function keys */
#define HNY_KEY_ESCAPE          ::Honey::Keycode::Escape
#define HNY_KEY_ENTER           ::Honey::Keycode::Enter
#define HNY_KEY_TAB             ::Honey::Keycode::Tab
#define HNY_KEY_BACKSPACE       ::Honey::Keycode::Backspace
#define HNY_KEY_INSERT          ::Honey::Keycode::Insert
#define HNY_KEY_DELETE          ::Honey::Keycode::Delete
#define HNY_KEY_RIGHT           ::Honey::Keycode::Right
#define HNY_KEY_LEFT            ::Honey::Keycode::Left
#define HNY_KEY_DOWN            ::Honey::Keycode::Down
#define HNY_KEY_UP              ::Honey::Keycode::Up
#define HNY_KEY_PAGE_UP         ::Honey::Keycode::PageUp
#define HNY_KEY_PAGE_DOWN       ::Honey::Keycode::PageDown
#define HNY_KEY_HOME            ::Honey::Keycode::Home
#define HNY_KEY_END             ::Honey::Keycode::End
#define HNY_KEY_CAPS_LOCK       ::Honey::Keycode::CapsLock
#define HNY_KEY_SCROLL_LOCK     ::Honey::Keycode::ScrollLock
#define HNY_KEY_NUM_LOCK        ::Honey::Keycode::NumLock
#define HNY_KEY_PRINT_SCREEN    ::Honey::Keycode::PrintScreen
#define HNY_KEY_PAUSE           ::Honey::Keycode::Pause
#define HNY_KEY_F1              ::Honey::Keycode::F1
#define HNY_KEY_F2              ::Honey::Keycode::F2
#define HNY_KEY_F3              ::Honey::Keycode::F3
#define HNY_KEY_F4              ::Honey::Keycode::F4
#define HNY_KEY_F5              ::Honey::Keycode::F5
#define HNY_KEY_F6              ::Honey::Keycode::F6
#define HNY_KEY_F7              ::Honey::Keycode::F7
#define HNY_KEY_F8              ::Honey::Keycode::F8
#define HNY_KEY_F9              ::Honey::Keycode::F9
#define HNY_KEY_F10             ::Honey::Keycode::F10
#define HNY_KEY_F11             ::Honey::Keycode::F11
#define HNY_KEY_F12             ::Honey::Keycode::F12
#define HNY_KEY_F13             ::Honey::Keycode::F13
#define HNY_KEY_F14             ::Honey::Keycode::F14
#define HNY_KEY_F15             ::Honey::Keycode::F15
#define HNY_KEY_F16             ::Honey::Keycode::F16
#define HNY_KEY_F17             ::Honey::Keycode::F17
#define HNY_KEY_F18             ::Honey::Keycode::F18
#define HNY_KEY_F19             ::Honey::Keycode::F19
#define HNY_KEY_F20             ::Honey::Keycode::F20
#define HNY_KEY_F21             ::Honey::Keycode::F21
#define HNY_KEY_F22             ::Honey::Keycode::F22
#define HNY_KEY_F23             ::Honey::Keycode::F23
#define HNY_KEY_F24             ::Honey::Keycode::F24
#define HNY_KEY_F25             ::Honey::Keycode::F25

/* Keypad */
#define HNY_KEY_KP_0            ::Honey::Keycode::KP0
#define HNY_KEY_KP_1            ::Honey::Keycode::KP1
#define HNY_KEY_KP_2            ::Honey::Keycode::KP2
#define HNY_KEY_KP_3            ::Honey::Keycode::KP3
#define HNY_KEY_KP_4            ::Honey::Keycode::KP4
#define HNY_KEY_KP_5            ::Honey::Keycode::KP5
#define HNY_KEY_KP_6            ::Honey::Keycode::KP6
#define HNY_KEY_KP_7            ::Honey::Keycode::KP7
#define HNY_KEY_KP_8            ::Honey::Keycode::KP8
#define HNY_KEY_KP_9            ::Honey::Keycode::KP9
#define HNY_KEY_KP_DECIMAL      ::Honey::Keycode::KPDecimal
#define HNY_KEY_KP_DIVIDE       ::Honey::Keycode::KPDivide
#define HNY_KEY_KP_MULTIPLY     ::Honey::Keycode::KPMultiply
#define HNY_KEY_KP_SUBTRACT     ::Honey::Keycode::KPSubtract
#define HNY_KEY_KP_ADD          ::Honey::Keycode::KPAdd
#define HNY_KEY_KP_ENTER        ::Honey::Keycode::KPEnter
#define HNY_KEY_KP_EQUAL        ::Honey::Keycode::KPEqual

#define HNY_KEY_LEFT_SHIFT      ::Honey::Keycode::LeftShift
#define HNY_KEY_LEFT_CONTROL    ::Honey::Keycode::LeftControl
#define HNY_KEY_LEFT_ALT        ::Honey::Keycode::LeftAlt
#define HNY_KEY_LEFT_SUPER      ::Honey::Keycode::LeftSuper
#define HNY_KEY_RIGHT_SHIFT     ::Honey::Keycode::RightShift
#define HNY_KEY_RIGHT_CONTROL   ::Honey::Keycode::RightControl
#define HNY_KEY_RIGHT_ALT       ::Honey::Keycode::RightAlt
#define HNY_KEY_RIGHT_SUPER     ::Honey::Keycode::RightSuper
#define HNY_KEY_MENU            ::Honey::Keycode::Menu
