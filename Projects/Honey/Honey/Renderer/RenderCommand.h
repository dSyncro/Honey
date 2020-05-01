#pragma once

#include "Renderer.h"

namespace Honey {

	class RenderCommand {

	public:

		static void Init();

		static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
		static void Clear() { s_RendererAPI->Clear(); }

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		static void DrawIndexed(const Reference<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}

	private:

		static Unique<RendererAPI> s_RendererAPI;

	};

}