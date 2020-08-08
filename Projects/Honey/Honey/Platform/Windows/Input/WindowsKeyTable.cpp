#include "WindowsKeyTable.h"

using namespace Honey;

Keycode WindowsKeyTable::_keycodes[512];
uint16_t WindowsKeyTable::_scancodes[512];

void WindowsKeyTable::Init()
{
	for (std::size_t i = 0; i < 512; i++)
	{
		_keycodes[i] = (Keycode)0;
		_scancodes[i] = 0;
	}

	_keycodes[0x00B] = Keycode::D0;
	_keycodes[0x002] = Keycode::D1;
	_keycodes[0x003] = Keycode::D2;
	_keycodes[0x004] = Keycode::D3;
	_keycodes[0x005] = Keycode::D4;
	_keycodes[0x006] = Keycode::D5;
	_keycodes[0x007] = Keycode::D6;
	_keycodes[0x008] = Keycode::D7;
	_keycodes[0x009] = Keycode::D8;
	_keycodes[0x00A] = Keycode::D9;
	_keycodes[0x01E] = Keycode::A;
	_keycodes[0x030] = Keycode::B;
	_keycodes[0x02E] = Keycode::C;
	_keycodes[0x020] = Keycode::D;
	_keycodes[0x012] = Keycode::E;
	_keycodes[0x021] = Keycode::F;
	_keycodes[0x022] = Keycode::G;
	_keycodes[0x023] = Keycode::H;
	_keycodes[0x017] = Keycode::I;
	_keycodes[0x024] = Keycode::J;
	_keycodes[0x025] = Keycode::K;
	_keycodes[0x026] = Keycode::L;
	_keycodes[0x032] = Keycode::M;
	_keycodes[0x031] = Keycode::N;
	_keycodes[0x018] = Keycode::O;
	_keycodes[0x019] = Keycode::P;
	_keycodes[0x010] = Keycode::Q;
	_keycodes[0x013] = Keycode::R;
	_keycodes[0x01F] = Keycode::S;
	_keycodes[0x014] = Keycode::T;
	_keycodes[0x016] = Keycode::U;
	_keycodes[0x02F] = Keycode::V;
	_keycodes[0x011] = Keycode::W;
	_keycodes[0x02D] = Keycode::X;
	_keycodes[0x015] = Keycode::Y;
	_keycodes[0x02C] = Keycode::Z;

	_keycodes[0x028] = Keycode::Apostrophe;
	_keycodes[0x02B] = Keycode::Backslash;
	_keycodes[0x033] = Keycode::Comma;
	_keycodes[0x00D] = Keycode::Equal;
	_keycodes[0x029] = Keycode::GraveAccent;
	_keycodes[0x01A] = Keycode::LeftBracket;
	_keycodes[0x00C] = Keycode::Minus;
	_keycodes[0x034] = Keycode::Period;
	_keycodes[0x01B] = Keycode::RightBracket;
	_keycodes[0x027] = Keycode::Semicolon;
	_keycodes[0x035] = Keycode::Slash;
	_keycodes[0x056] = Keycode::World2;

	_keycodes[0x00E] = Keycode::Backspace;
	_keycodes[0x153] = Keycode::Delete;
	_keycodes[0x14F] = Keycode::End;
	_keycodes[0x01C] = Keycode::Enter;
	_keycodes[0x001] = Keycode::Escape;
	_keycodes[0x147] = Keycode::Home;
	_keycodes[0x152] = Keycode::Insert;
	_keycodes[0x15D] = Keycode::Menu;
	_keycodes[0x151] = Keycode::PageDown;
	_keycodes[0x149] = Keycode::PageUp;
	_keycodes[0x045] = Keycode::Pause;
	_keycodes[0x146] = Keycode::Pause;
	_keycodes[0x039] = Keycode::Space;
	_keycodes[0x00F] = Keycode::Tab;
	_keycodes[0x03A] = Keycode::CapsLock;
	_keycodes[0x145] = Keycode::NumLock;
	_keycodes[0x046] = Keycode::ScrollLock;
	_keycodes[0x03B] = Keycode::F1;
	_keycodes[0x03C] = Keycode::F2;
	_keycodes[0x03D] = Keycode::F3;
	_keycodes[0x03E] = Keycode::F4;
	_keycodes[0x03F] = Keycode::F5;
	_keycodes[0x040] = Keycode::F6;
	_keycodes[0x041] = Keycode::F7;
	_keycodes[0x042] = Keycode::F8;
	_keycodes[0x043] = Keycode::F9;
	_keycodes[0x044] = Keycode::F10;
	_keycodes[0x057] = Keycode::F11;
	_keycodes[0x058] = Keycode::F12;
	_keycodes[0x064] = Keycode::F13;
	_keycodes[0x065] = Keycode::F14;
	_keycodes[0x066] = Keycode::F15;
	_keycodes[0x067] = Keycode::F16;
	_keycodes[0x068] = Keycode::F17;
	_keycodes[0x069] = Keycode::F18;
	_keycodes[0x06A] = Keycode::F19;
	_keycodes[0x06B] = Keycode::F20;
	_keycodes[0x06C] = Keycode::F21;
	_keycodes[0x06D] = Keycode::F22;
	_keycodes[0x06E] = Keycode::F23;
	_keycodes[0x076] = Keycode::F24;
	_keycodes[0x038] = Keycode::LeftAlt;
	_keycodes[0x01D] = Keycode::LeftControl;
	_keycodes[0x02A] = Keycode::LeftShift;
	_keycodes[0x15B] = Keycode::LeftSuper;
	_keycodes[0x137] = Keycode::PrintScreen;
	_keycodes[0x138] = Keycode::RightAlt;
	_keycodes[0x11D] = Keycode::RightControl;
	_keycodes[0x036] = Keycode::RightShift;
	_keycodes[0x15C] = Keycode::RightSuper;
	_keycodes[0x150] = Keycode::Down;
	_keycodes[0x14B] = Keycode::Left;
	_keycodes[0x14D] = Keycode::Right;
	_keycodes[0x148] = Keycode::Up;

	_keycodes[0x052] = Keycode::KP0;
	_keycodes[0x04F] = Keycode::KP1;
	_keycodes[0x050] = Keycode::KP2;
	_keycodes[0x051] = Keycode::KP3;
	_keycodes[0x04B] = Keycode::KP4;
	_keycodes[0x04C] = Keycode::KP5;
	_keycodes[0x04D] = Keycode::KP6;
	_keycodes[0x047] = Keycode::KP7;
	_keycodes[0x048] = Keycode::KP8;
	_keycodes[0x049] = Keycode::KP9;
	_keycodes[0x04E] = Keycode::KPAdd;
	_keycodes[0x053] = Keycode::KPDecimal;
	_keycodes[0x135] = Keycode::KPDivide;
	_keycodes[0x11C] = Keycode::KPEnter;
	_keycodes[0x059] = Keycode::KPEqual;
	_keycodes[0x037] = Keycode::KPMultiply;
	_keycodes[0x04A] = Keycode::KPSubtract;

	uint32_t scancode = 0;
	for (scancode; scancode < 512; scancode++)
	{
		uint32_t keycode = (uint32_t)_keycodes[scancode];
		if (keycode) _scancodes[keycode] = scancode;
	}
}
