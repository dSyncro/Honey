#pragma once

#include <Honey/Renderer/RendererAPI.h>

namespace Honey {

	class OpenGLRendererAPI final : public RendererAPI {

	public:

		virtual void Init() override;

		virtual void SetClearColor(const Math::Vector4& color) override;
		virtual void Clear() const override;

		virtual void SetViewport(Math::Vector2 location, Math::Vector2 size) override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void DrawIndexed(const Reference<VertexArray>& vertexArray, uint32_t indexCount = 0) override;

	};

}
