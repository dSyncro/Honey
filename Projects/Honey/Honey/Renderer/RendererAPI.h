#pragma once

#include "VertexArray.h"

#include <Honey/Core/Color.h>
#include <Honey/Math/Vectors.h>

namespace Honey {

	class RendererAPI {

	public:

		enum class API {
			None,
			OpenGL,
			DirectX
		};

		virtual ~RendererAPI() = default;

		virtual void Init() = 0;

		virtual void Clear() const = 0;
		virtual void ClearDepthBuffer() const = 0;
		virtual void SetClearColor(const Color& color) = 0;

		virtual void SetViewport(Math::Vector2 location, Math::Vector2 size) = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void DrawIndexed(const Reference<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

		static API GetAPI() { return s_API; }
		static Unique<RendererAPI> Create();

	private:

		static API s_API;

	};
}
