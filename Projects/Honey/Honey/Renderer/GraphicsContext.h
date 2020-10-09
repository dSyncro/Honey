#pragma once

#include <Honey/Core/MemoryManagement.h>

namespace Honey {

	/**
	 * @brief Graphic context implementation.
	*/
	class GraphicsContext {

	public:

		virtual ~GraphicsContext() = default;

		/**
		 * @brief Initialize context.
		*/
		virtual void init() = 0;

		/**
		 * @brief Swap context buffers.
		*/
		virtual void swapBuffers() = 0;

		/**
		 * @brief Create a new context for a specified window.
		 * @param window The window.
		 * @return A new memory managed context.
		*/
		static Unique<GraphicsContext> create(void* window);
	};

}
