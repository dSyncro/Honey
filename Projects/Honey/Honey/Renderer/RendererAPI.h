#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Honey {

	class RendererAPI {

	public:

		enum class API {
			None,
			OpenGL,
		};

		virtual void Init() = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() const = 0;

		virtual void DrawIndexed(const Reference<VertexArray>& vertexArray) = 0;

		static API GetAPI() { return s_API; }

	private:

		static API s_API;

	};
}