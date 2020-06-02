#pragma once

#include <Honey/Renderer/GraphicsContext.h>

extern "C" {
#include <GLFW/glfw3.h>
}

namespace Honey {

	class OpenGLContext final : public GraphicsContext {

	public:

		OpenGLContext(GLFWwindow* handle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:

		GLFWwindow* _handle;

	};

}