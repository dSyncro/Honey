#pragma once

#include <Honey/Renderer/RendererAPI.h>

namespace Honey {

	/**
	 * @brief OpenGL renderer API implementation.
	*/
	class OpenGLRendererAPI final : public RendererAPI {

	public:

		/**
		 * @brief Initialize renderer API.
		*/
		virtual void init() override;

		/**
		 * @brief Clear renderer.
		*/
		virtual void clear() const override;

		/**
		 * @brief Clear depth buffer.
		*/
		virtual void clearDepthBuffer() const override;

		/**
		 * @brief Set renderer clear color.
		 * @param color The color.
		*/
		virtual void setClearColor(const Color& color) override;

		/**
		 * @brief Set rendering viewport.
		 * @param location Viewport location.
		 * @param size Viewport size.
		*/
		virtual void setViewport(Math::Vector2 location, Math::Vector2 size) override;

		/**
		 * @brief Set rendering viewport.
		 * @param x Viewport position X.
		 * @param y Viewport position Y.
		 * @param width Viewport width.
		 * @param height Viewport height.
		*/
		virtual void setViewport(UInt x, UInt y, UInt width, UInt height) override;

		virtual void drawIndexed(const Reference<VertexArray>& vertexArray, UInt indexCount = 0) override;

	};

}
