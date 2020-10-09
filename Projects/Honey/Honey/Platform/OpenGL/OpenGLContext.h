#pragma once

#include <Honey/Renderer/GraphicsContext.h>

namespace Honey {

	/**
	 * @brief OpenGL graphics context implementation.
	*/
	class OpenGLContext final : public GraphicsContext {

	public:

		/**
		 * @brief Construct OpenGLContext from handle.
		 * @param handle The handle.
		*/
		OpenGLContext(void* handle);

		/**
		 * @brief Initialize context.
		*/
		virtual void init() override;

		/**
		 * @brief Swap context buffers.
		*/
		virtual void swapBuffers() override;

	private:

		void* _handle;

	};

}
