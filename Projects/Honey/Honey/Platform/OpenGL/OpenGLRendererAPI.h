#pragma once

#include <Honey/Renderer/RendererAPI.h>

namespace Honey {

	class OpenGLRendererAPI : public RendererAPI {

	public:

		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() const override;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void DrawIndexed(const Reference<VertexArray>& vertexArray) override;

	};

}