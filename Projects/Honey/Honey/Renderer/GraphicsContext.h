#pragma once

#include <Honey/Core.h>

namespace Honey {

	class GraphicsContext {

	public:

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Unique<GraphicsContext> Create(void* window);
	};

}