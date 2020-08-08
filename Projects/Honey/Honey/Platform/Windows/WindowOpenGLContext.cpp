#include <Honey/Platform/OpenGL/OpenGLContext.h>

#include <Honey/Core.h>

extern "C" {
#include <glad/glad.h>
}

using namespace Honey;

OpenGLContext::OpenGLContext(void* handle) : _handle(handle)
{
	HNY_CORE_ASSERT(_handle, "Window handle is null!");
}

void* GetAnyGLFuncAddress(const char* name)
{
	void* p = (void*)wglGetProcAddress(name);
	if (p == 0 ||
		(p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||
		(p == (void*)-1))
	{
		HMODULE module = LoadLibraryA("opengl32.dll");
		if (module) p = (void*)GetProcAddress(module, name);
		else HNY_CORE_ASSERT(false, "Unable to get proc address!");
	}

	return p;
}

void OpenGLContext::Init()
{
	HNY_PROFILE_FUNCTION();

	HDC      hdc;
	HGLRC    hglrc;

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	// obtain a device context for the window  
	hdc = GetDC((HWND)_handle);

	int  letWindowsChooseThisPixelFormat;
	letWindowsChooseThisPixelFormat = ChoosePixelFormat(hdc, &pfd);
	BOOL setpformat = SetPixelFormat(hdc, letWindowsChooseThisPixelFormat, &pfd);

	if (hglrc = wglCreateContext(hdc))
	{
		if (wglMakeCurrent(hdc, hglrc))
		{
			const GLADloadproc proc = (GLADloadproc)GetAnyGLFuncAddress;
			int status = gladLoadGLLoader(proc);
			HNY_CORE_ASSERT(status, "Failed to init GLAD!");
		}
	}
	

	HNY_CORE_INFO("## OpenGL Info ##");
	HNY_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
	HNY_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	HNY_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
	HNY_CORE_INFO("#################");
}

void OpenGLContext::SwapBuffers()
{
	HNY_PROFILE_FUNCTION();

	//glfwSwapBuffers((GLFWwindow*)_handle);
}
