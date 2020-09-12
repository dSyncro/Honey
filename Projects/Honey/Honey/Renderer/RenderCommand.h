#pragma once

#include "Renderer.h"

namespace Honey {

	class RenderCommand {

	public:

		static void Init();

		static void Clear() { s_RendererAPI->Clear(); }
		static void ClearDepthBuffer() { s_RendererAPI->ClearDepthBuffer(); }
		static void SetClearColor(const Color& color) { s_RendererAPI->SetClearColor(color); }

		static void SetViewport(Math::Vector2 location, Math::Vector2 size);
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		static void DrawIndexed(const Reference<VertexArray>& vertexArray, uint32_t indexCount = 0);

	private:

		static Unique<RendererAPI> s_RendererAPI;

	};

}
