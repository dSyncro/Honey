#pragma once

namespace Honey {

	enum class RendererAPI {
		None,
		OpenGL,
	};

	class Renderer {

	public:

		inline static RendererAPI GetAPI() { return s_RendererAPI; }

	private:

		static RendererAPI s_RendererAPI;
	};

}