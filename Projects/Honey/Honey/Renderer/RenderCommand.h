#pragma once

#include "Renderer.h"

namespace Honey {

	/**
	 * @brief Render commands.
	*/
	class RenderCommand {

	public:

		/**
		 * @brief Initialize rendering.
		*/
		static void init();

		/**
		 * @brief Clear viewport.
		*/
		static void clear() { s_RendererAPI->clear(); }

		/**
		 * @brief Clear depth buffer.
		*/
		static void clearDepthBuffer() { s_RendererAPI->clearDepthBuffer(); }

		/**
		 * @brief Set a new clear color.
		 * @param color The new color.
		*/
		static void setClearColor(const Color& color) { s_RendererAPI->setClearColor(color); }

		/**
		 * @brief Set viewport.
		 * @param location Viewport position.
		 * @param size Viewport size.
		*/
		static void setViewport(Math::Vector2 location, Math::Vector2 size);

		/**
		 * @brief Set viewport.
		 * @param x Viewport position X.
		 * @param y Viewport position Y.
		 * @param width Viewport width.
		 * @param height Viewport height.
		*/
		static void setViewport(UInt x, UInt y, UInt width, UInt height);

		/**
		 * @brief Draw indexed elements.
		 * @param vertexArray Source vertex array.
		 * @param indexCount Index count.
		*/
		static void drawIndexed(const Reference<VertexArray>& vertexArray, UInt indexCount = 0);

	private:

		static Unique<RendererAPI> s_RendererAPI;

	};

}
