#pragma once

#include <Honey/Renderer/GraphicsContext.h>

struct GLFWwindow;

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
