#include <Honey/Platform/OpenGL/OpenGLContext.h>

#include <Honey/Core.h>

extern "C" {
#include <glad/glad.h>
}

using namespace Honey;

static HDC s_Hdc;

OpenGLContext::OpenGLContext(void* handle) : _handle(handle)
{
	HNY_CORE_ASSERT(_handle, "Window handle is null!");
}

static void* GetAnyGLFuncAddress(const char* name)
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
	s_Hdc = GetDC((HWND)_handle);

	int  letWindowsChooseThisPixelFormat;
	letWindowsChooseThisPixelFormat = ChoosePixelFormat(s_Hdc, &pfd);
	BOOL setpformat = SetPixelFormat(s_Hdc, letWindowsChooseThisPixelFormat, &pfd);

	HGLRC hglrc = wglCreateContext(s_Hdc);
	if (hglrc)
	{
		if (wglMakeCurrent(s_Hdc, hglrc))
		{
			const GLADloadproc proc = (GLADloadproc)GetAnyGLFuncAddress;
			int status = gladLoadGLLoader(proc);
			HNY_CORE_ASSERT(status, "Failed to init GLAD!");
		}
		else HNY_CORE_ASSERT(false, "Failed to set OpenGL Context!");
	}
	else HNY_CORE_ASSERT(false, "Failed to init OpenGL Context!");
	

	HNY_CORE_INFO("## OpenGL Info ##");
	HNY_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
	HNY_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	HNY_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
	HNY_CORE_INFO("#################");
}

void OpenGLContext::SwapBuffers()
{
	HNY_PROFILE_FUNCTION();

	::SwapBuffers(s_Hdc);
}
