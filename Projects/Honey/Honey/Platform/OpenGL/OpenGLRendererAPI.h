#pragma once

#include <Honey/Renderer/RendererAPI.h>

namespace Honey {

	class OpenGLRendererAPI : public RendererAPI {

	public:

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() const override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

	};

}