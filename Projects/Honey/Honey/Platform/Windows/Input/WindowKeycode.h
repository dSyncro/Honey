#pragma once

#include <Honey/Platform/Windows/WindowsHeader.h>
#include <Honey/Input/Keycode.h>

#include <ostream>

namespace Honey {

	typedef enum class WindowKeycode : uint16_t
	{
		Backspace = VK_BACK,
		Tab = VK_TAB,
		Clear = VK_CLEAR,
		Return = VK_RETURN,
		Shift = VK_SHIFT,
		Control = VK_CONTROL,
		Alt = VK_MENU,
		Pause = VK_PAUSE,
		CapsLock = VK_CAPITAL,
		Kana = VK_KANA,
		Hangul = VK_HANGUL,
		Junja = VK_JUNJA,
		Final = VK_FINAL,
		Hanja = VK_HANJA,
		Kanji = VK_KANJI,
		Escape = VK_ESCAPE,
		Convert = VK_CONVERT,
		NonConvert = VK_NONCONVERT,
		Accept = VK_ACCEPT,
		ModeChange = VK_MODECHANGE,
		Space = VK_SPACE,
		PageUp = VK_PRIOR,
		PageDown = VK_NEXT,
		End = VK_END,
		Home = VK_HOME,
		Left = VK_LEFT,
		Up = VK_UP,
		Right = VK_RIGHT,
		Down = VK_DOWN,
		Select = VK_SELECT,
		Print = VK_PRINT,
		Execute = VK_EXECUTE,
		Print = VK_SNAPSHOT,
		Insert = VK_INSERT,
		Delete = VK_DELETE,
		Help = VK_HELP,
		D0 = 0x30,
		D1 = 0x31,
		D2 = 0x32,
		D3 = 0x33,
		D4 = 0x34,
		D5 = 0x35,
		D6 = 0x36,
		D7 = 0x37,
		D8 = 0x38,
		D9 = 0x39,
		A = 0x41,
		B = 0x42,
		C = 0x43,
		D = 0x44,
		E = 0x45,
		F = 0x46,
		G = 0x47,
		H = 0x48,
		I = 0x49,
		J = 0x4A,
		K = 0x4B,
		L = 0x4C,
		M = 0x4D,
		N = 0x4E,
		O = 0x4F,
		P = 0x50,
		Q = 0x51,
		R = 0x52,
		S = 0x53,
		T = 0x54,
		U = 0x55,
		V = 0x56,
		W = 0x57,
		X = 0x58,
		Y = 0x59,
		Z = 0x5A,
		LWin = VK_LWIN,
		RWin = VK_RWIN,
		Applications = VK_APPS,
		Sleep = VK_SLEEP,
		Numpad0 = VK_NUMPAD0,
		Numpad1 = VK_NUMPAD1,
		Numpad2 = VK_NUMPAD2,
		Numpad3 = VK_NUMPAD3,
		Numpad4 = VK_NUMPAD4,
		Numpad5 = VK_NUMPAD5,
		Numpad6 = VK_NUMPAD6,
		Numpad7 = VK_NUMPAD7,
		Numpad8 = VK_NUMPAD8,
		Numpad9 = VK_NUMPAD9,
		Multiply = VK_MULTIPLY,
		Add = VK_ADD,
		Separator = VK_SEPARATOR,
		Subtract = VK_SUBTRACT,
		Decimal = VK_DECIMAL,
		Divide = VK_DIVIDE,
		F1 = VK_F1,
		F2 = VK_F2,
		F3 = VK_F3,
		F4 = VK_F4,
		F5 = VK_F5,
		F6 = VK_F6,
		F7 = VK_F7,
		F8 = VK_F8,
		F9 = VK_F9,
		F10 = VK_F10,
		F11 = VK_F11,
		F12 = VK_F12,
		F13 = VK_F13,
		F14 = VK_F14,
		F15 = VK_F15,
		F16 = VK_F16,
		F17 = VK_F17,
		F18 = VK_F18,
		F19 = VK_F19,
		F20 = VK_F20,
		F21 = VK_F21,
		F22 = VK_F22,
		F23 = VK_F23,
		F24 = VK_F24,
		Numlock = VK_NUMLOCK,
		ScrollLock = VK_SCROLL,
		LShift = VK_LSHIFT,
		RShift = VK_RSHIFT,
		LControl = VK_LCONTROL,
		RControl = VK_RCONTROL,
		LMenu = VK_LMENU,
		RMenu = VK_RMENU,
		BrowserBack = VK_BROWSER_BACK,
		BrowserForward = VK_BROWSER_FORWARD,
		BrowserRefresh = VK_BROWSER_REFRESH,
		BrowserStop = VK_BROWSER_STOP,
		BrowserSearch = VK_BROWSER_SEARCH,
		BrowserFavorites = VK_BROWSER_FAVORITES,
		BrowserHome = VK_BROWSER_HOME,
		VolumeMute = VK_VOLUME_MUTE,
		VolumeDown = VK_VOLUME_DOWN,
		VolumeUp = VK_VOLUME_UP,
		MediaNextTrack = VK_MEDIA_NEXT_TRACK,
		MediaPreviousTrack = VK_MEDIA_PREV_TRACK,
		MediaStop = VK_MEDIA_STOP,
		MediaPlayPause = VK_MEDIA_PLAY_PAUSE,
		LaunchMail = VK_LAUNCH_MAIL,
		LaunchMedia = VK_LAUNCH_MEDIA_SELECT,
		LaunchApp1 = VK_LAUNCH_APP1,
		LaunchApp2 = VK_LAUNCH_APP2,
		Oem1 = VK_OEM_1,
		OemPlus = VK_OEM_PLUS,
		OemComma = VK_OEM_COMMA,
		OemMinus = VK_OEM_MINUS,
		OemPeriod = VK_OEM_PERIOD,
		Oem2 = VK_OEM_2,
		Oem3 = VK_OEM_3,
		Oem4 = VK_OEM_4,
		Oem5 = VK_OEM_5,
		Oem6 = VK_OEM_6,
		Oem7 = VK_OEM_7,
		Oem8 = VK_OEM_8,
		Oem102 = VK_OEM_102,
		ProcessKey = VK_PROCESSKEY,
		Packet = VK_PACKET,
		Attn = VK_ATTN,
		CrSel = VK_CRSEL,
		ExSel = VK_EXSEL,
		ErEOF = VK_EREOF,
		Play = VK_PLAY,
		Zoom = VK_ZOOM,
		PA1 = VK_PA1,
		OemClear = VK_OEM_CLEAR
	} WinKey;

	inline std::ostream& operator<<(std::ostream& os, WindowKeycode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}

}
