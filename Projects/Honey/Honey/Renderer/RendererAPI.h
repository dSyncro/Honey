#pragma once

#include "VertexArray.h"

#include <Honey/Core/Color.h>
#include <Honey/Math/Vectors.h>

namespace Honey {
	
	/**
	 * @brief class interfacing with Rendering API indirectly.
	*/
	class RendererAPI {

	public:

		/**
		 * @brief Supported APIs.
		*/
		enum class API {
			None, /** @brief No rendering API. */
			OpenGL, /** @brief OpenGL. */
			DirectX /** @brief DirectX (not implemented yet). */
		};

		virtual ~RendererAPI() = default;

		/**
		 * @brief Initialize rendering API.
		*/
		virtual void init() = 0;

		/**
		 * @brief Clear screen and related buffers.
		*/
		virtual void clear() const = 0;

		/**
		 * @brief Clear depth buffer only.
		*/
		virtual void clearDepthBuffer() const = 0;

		/**
		 * @brief Set a new clear color.
		 * @param color New color.
		*/
		virtual void setClearColor(const Color& color) = 0;

		/**
		 * @brief Set viewport.
		 * @param location Viewport position.
		 * @param size Viewport size.
		*/
		virtual void setViewport(Math::Vector2 location, Math::Vector2 size) = 0;

		/**
		 * @brief Set viewport.
		 * @param x Viewport position X.
		 * @param y Viewport position Y.
		 * @param width Viewport width.
		 * @param height Viewport height.
		*/
		virtual void setViewport(UInt x, UInt y, UInt width, UInt height) = 0;

		/**
		 * @brief Draw indexed elements.
		 * @param vertexArray Source vertex array.
		 * @param indexCount Index count.
		*/
		virtual void drawIndexed(const Reference<VertexArray>& vertexArray, UInt indexCount = 0) = 0;

		/**
		 * @brief Get current Rendering API.
		 * @return Current rendering API.
		*/
		static API getAPI() { return s_API; }

		/**
		 * @brief Create RendererAPI.
		 * @return A new memory managed RendererAPI.
		*/
		static Unique<RendererAPI> create();

	private:

		static API s_API;

	};
}
