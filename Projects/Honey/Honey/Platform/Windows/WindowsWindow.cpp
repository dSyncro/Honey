#include "WindowsWindow.h"

#include <Honey/Events/KeyEvents.h>
#include <Honey/Events/MouseEvents.h>
#include <Honey/Events/WindowEvents.h>
#include <Honey/Renderer/Renderer.h>
#include <Honey/Platform/OpenGL/OpenGLContext.h>
#include <Honey/Platform/Windows/Input/WindowsKeyTable.h>
#include <Honey/Platform/ImGui/ImGuiWin32Implementation.h>
#include <Honey/Timing/Time.h>

#include "WindowsMessageMap.h"

using namespace Honey;

static uint8_t s_WindowCount = 0;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

WindowsWindow::WindowsWindow(const WindowProperties& properties)
{
	HNY_PROFILE_FUNCTION();

	Init(properties);
}

WindowsWindow::~WindowsWindow()
{
	HNY_PROFILE_FUNCTION();

	Shutdown();
}

void WindowsWindow::Init(const WindowProperties& properties)
{
	HNY_PROFILE_FUNCTION();

	HNY_CORE_INFO("Creating window {0} ({1}; {2})", properties.Title, properties.Width, properties.Height);

	_data.Width = properties.Width;
	_data.Height = properties.Height;
	_data.Title = properties.Title;

	_window = CreateWindowExA(0, WindowClass::GetName(), _data.Title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, _data.Width, _data.Height, 0, 0, WindowClass::GetInstance(), &_data);
	s_WindowCount++;

	ShowWindow(_window, SW_SHOW);

	// Init the context
	_context = GraphicsContext::Create(_window);
	_context->Init();
}

void WindowsWindow::Shutdown()
{
	HNY_PROFILE_FUNCTION();

	DestroyWindow(_window);
	s_WindowCount--;
	if (!s_WindowCount) PostQuitMessage(0);
}

void WindowsWindow::PollEvents()
{
	try
	{
		MSG message;
		while (PeekMessageW(&message, _window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
	catch (const TidyException& e)
	{
		MessageBoxA(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBoxA(nullptr, "No Details Available.", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}

	Engine::_timer.MarkFrame();
}

void WindowsWindow::OnUpdate()
{
	HNY_PROFILE_FUNCTION();

	PollEvents();
	_context->SwapBuffers();
}

void WindowsWindow::SetTitle(const std::string& title)
{
	SetWindowTextA(_window, title.c_str());
}

void WindowsWindow::SetVSync(bool enabled)
{
	HNY_PROFILE_FUNCTION();

	// glfwSwapInterval(enabled);
}

bool WindowsWindow::IsVSyncEnabled() const
{
	return false;
} // _data.VSync; }

LRESULT WindowsWindow::WindowsEventCallbackSetup(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		WindowData* data = static_cast<WindowData*>(pCreate->lpCreateParams);
		SetWindowLongPtr(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(data));
		SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WindowsWindow::WindowsEventCallbackThrunk));
		WindowsEventCallbackThrunk(window, msg, wParam, lParam);
	}

	return DefWindowProc(window, msg, wParam, lParam);
}

LRESULT WindowsWindow::WindowsEventCallbackThrunk(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(ImGui_ImplWin32_WndProcHandler(window, msg, wParam, lParam)) return true;
	WindowData& data = *reinterpret_cast<WindowData*>(GetWindowLongPtr(window, GWLP_USERDATA));
	switch (msg)
	{
		case WM_SIZE: 
		{
			UINT w = LOWORD(lParam);
			UINT h = HIWORD(lParam);
			WindowResizeCallback(data, w, h);
			break;
		}
			
		case WM_CLOSE:
		{
			WindowCloseCallback(data);
			break;
		}

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			int repeatCount = LOWORD(lParam);
			const KeyState action = (HIWORD(lParam) & KF_UP) ? KeyState::Released : KeyState::Pressed;
			const KeyMods mods = (KeyMods)Input::GetKeyMods();

			uint32_t scancode = (HIWORD(lParam) & (KF_EXTENDED | 0xff));
			if (!scancode)
			{
				// NOTE: Some synthetic key messages have a scancode of zero
				// HACK: Map the virtual key back to a usable scancode
				scancode = MapVirtualKeyW((UINT)wParam, MAPVK_VK_TO_VSC);
			}

			Keycode key = WindowsKeyTable::ScancodeToKeycode(scancode);

			// The Ctrl keys require special handling
			if (wParam == VK_CONTROL)
			{
				if (HIWORD(lParam) & KF_EXTENDED)
				{
					// Right side keys have the extended key bit set
					key = Keycode::RightControl;
				}
				else
				{
					// NOTE: Alt Gr sends Left Ctrl followed by Right Alt
					// HACK: We only want one event for Alt Gr, so if we detect
					//       this sequence we discard this Left Ctrl message now
					//       and later report Right Alt normally
					MSG next;
					const DWORD time = GetMessageTime();

					if (PeekMessageW(&next, NULL, 0, 0, PM_NOREMOVE))
					{
						if (next.message == WM_KEYDOWN ||
							next.message == WM_SYSKEYDOWN ||
							next.message == WM_KEYUP ||
							next.message == WM_SYSKEYUP)
						{
							if (next.wParam == VK_MENU &&
								(HIWORD(next.lParam) & KF_EXTENDED) &&
								next.time == time)
							{
								// Next message is Right Alt down so discard this
								break;
							}
						}
					}

					// This is a regular Left Ctrl message
					key = Keycode::LeftControl;
				}
			}
			else if (wParam == VK_PROCESSKEY)
			{
				// IME notifies that keys have been filtered by setting the
				// virtual key-code to VK_PROCESSKEY
				break;
			}

			if (action == KeyState::Released && wParam == VK_SHIFT)
			{
				// HACK: Release both Shift keys on Shift up event, as when both
				//       are pressed the first release does not emit any event
				// NOTE: The other half of this is in _glfwPlatformPollEvents
				WindowKeyCallback(data, Keycode::LeftShift, scancode, action, mods, repeatCount);
				WindowKeyCallback(data, Keycode::RightShift, scancode, action, mods, repeatCount);
			}
			else if (wParam == VK_SNAPSHOT)
			{
				// HACK: Key down is not reported for the Print Screen key
				WindowKeyCallback(data, key, scancode, KeyState::Pressed, mods, repeatCount);
				WindowKeyCallback(data, key, scancode, KeyState::Released, mods, repeatCount);
			}
			else
				WindowKeyCallback(data, key, scancode, action, mods, repeatCount);

			break;
		}

		case WM_CHAR:
		{
			uint32_t scancode = (HIWORD(lParam) & (KF_EXTENDED | 0xff));
			WindowCharCallback(data, WindowsKeyTable::ScancodeToKeycode(scancode));
			break;
		}

		case WM_MOUSEWHEEL:
		{
			double delta = GET_WHEEL_DELTA_WPARAM(wParam) / (double)WHEEL_DELTA;
			WindowScrollCallback(data, delta, 0);
			break;
		}

		case WM_MOUSEHWHEEL:
		{
			double delta = GET_WHEEL_DELTA_WPARAM(wParam) / (double)WHEEL_DELTA;
			WindowScrollCallback(data, 0, delta);
			break;
		}

		case WM_MOUSEMOVE:
		{
			UINT x = GET_X_LPARAM(lParam);
			UINT y = GET_Y_LPARAM(lParam);
			WindowCursorPositionCallback(data, x, y);
			break;
		}

		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_XBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_XBUTTONUP:
		{
			MouseButton button;
			KeyState action;

			if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP)
				button = MouseButton::ButtonLeft;
			else if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP)
				button = MouseButton::ButtonRight;
			else if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP)
				button = MouseButton::ButtonMiddle;
			else if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
				button = MouseButton::Button4;
			else
				button = MouseButton::Button5;

			if (msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN ||
				msg == WM_MBUTTONDOWN || msg == WM_XBUTTONDOWN)
				action = KeyState::Pressed;
			else
				action = KeyState::Released;

			WindowMouseCallback(data, button, action, (KeyMods)Input::GetKeyMods());

			break;
		}

		default: return DefWindowProc(window, msg, wParam, lParam);
	}

	return 0;
}

void WindowsWindow::WindowResizeCallback(WindowData& data, int width, int height)
{
	data.Width = width;
	data.Height = height;

	WindowResizeEvent e(width, height);
	if (data.Callback) data.Callback(e);
}

void WindowsWindow::WindowCloseCallback(WindowData& data)
{
	WindowCloseEvent e;
	data.Callback(e);
}

void WindowsWindow::WindowKeyCallback(WindowData& data, Keycode keycode, int scancode, KeyState action, KeyMods mods, int repeat)
{
	switch (action)
	{
		case KeyState::Pressed:
		{
			KeyPressedEvent e(keycode, repeat);
			data.Callback(e);
			return;
		}

		case KeyState::Released:
		{
			KeyReleasedEvent e(keycode);
			data.Callback(e);
			return;
		}
	}
	
}

void WindowsWindow::WindowCharCallback(WindowData& data, Keycode keycode)
{
	KeyTypedEvent e(keycode);
	data.Callback(e);
}


void WindowsWindow::WindowMouseCallback(WindowData& data, MouseButton button, KeyState action, KeyMods mods)
{
	switch (action)
	{
		case KeyState::Pressed:
		{
			MouseButtonPressedEvent e(button);
			data.Callback(e);
			return;
		}

		case KeyState::Released:
		{
			MouseButtonReleasedEvent e(button);
			data.Callback(e);
			return;
		}
	}
}

void WindowsWindow::WindowScrollCallback(WindowData& data, double xOffset, double yOffset)
{
	MouseScrolledEvent e((float)xOffset, (float)yOffset);
	data.Callback(e);
}

void WindowsWindow::WindowCursorPositionCallback(WindowData& data, double xOffset, double yOffset)
{
	MouseMovedEvent e((float)xOffset, (float)yOffset);
	data.Callback(e);
}

WindowsWindow::WindowClass::WindowClass() : _instance(GetModuleHandle(nullptr))
{
	WNDCLASSEXA wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = &WindowsWindow::WindowsEventCallbackSetup;
	wc.hInstance = _instance;
	wc.style = CS_OWNDC;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = nullptr;
	wc.hIconSm = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();

	RegisterClassExA(&wc);
}

WindowsWindow::WindowClass::~WindowClass()
{
	UnregisterClassA(GetName(), GetInstance());
}

const char* WindowsWindow::WindowClass::GetName() noexcept
{
	return _name;
}

HINSTANCE WindowsWindow::WindowClass::GetInstance() noexcept
{
	return Get()._instance;
}

const char* WindowsWindow::Exception::what() const noexcept
{
	_whatBuffer = std::string(GetType()) + '\n' 
		+ "[ErrorCode] " + std::to_string(GetErrorCode()) 
		+ "\n[Description] " + GetErrorString() + '\n' 
		+ GetOriginString();
	return _whatBuffer.c_str();
}

std::string WindowsWindow::Exception::TranslateErrorCode(HRESULT result) noexcept
{
	char* msgBuffer = nullptr;
	DWORD msgLen = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, result, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&msgBuffer),
		0, nullptr
	);

	if (!msgLen) return "Unknown Error Code";

	std::string error = msgBuffer;
	LocalFree(msgBuffer);
	return error;
}
