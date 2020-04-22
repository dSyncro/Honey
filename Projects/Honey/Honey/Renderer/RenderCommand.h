#pragma once

#include "Renderer.h"

namespace Honey {

	class RenderCommand {

	public:

		static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
		static void Clear() { s_RendererAPI->Clear(); }

		static void DrawIndexed(const Reference<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}

	private:

		static RendererAPI* s_RendererAPI;

	};

}