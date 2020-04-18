#pragma once

#include "RendererAPI.h"

namespace Honey {

	class Renderer {

	public:

		inline static RendererAPI GetAPI() { return s_RendererAPI; }

	private:

		static RendererAPI s_RendererAPI;
	};

}