#pragma once

#include <Honey/Renderer/GraphicsContext.h>

namespace Honey {

	class OpenGLContext final : public GraphicsContext {

	public:

		OpenGLContext(void* handle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:

		void* _handle;

	};

}
