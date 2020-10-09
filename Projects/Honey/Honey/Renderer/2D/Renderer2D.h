#pragma once

#include "Quad.h"

#include <Honey/Math/Vectors.h>
#include <Honey/Math/Matrix/Matrix4x4.h>
#include <Honey/Renderer/Camera/Camera.h>
#include <Honey/Renderer/Camera/OrthographicCamera.h>
#include <Honey/Renderer/2D/Sprite.h>
#include <Honey/Renderer/2D/UI/Text/FontAtlas.h>

namespace Honey {

	/**
	 * @brief 2D Renderer implementation.
	*/
	class Renderer2D {

	public:

		// Pure static class

		Renderer2D() = delete;
		Renderer2D(const Renderer2D&) = delete;
		Renderer2D& operator =(const Renderer2D&) = delete;

		/**
		 * @brief Render statistics.
		*/
		struct Statistics {

			/** @brief Renderer draw calls. */
			UInt drawCalls = 0;

			/** @brief Renderer quad count. */
			UInt quadCount = 0;

			/**
			 * @brief Get rendered triangles count.
			 * @return Triangle count.
			*/
			UInt getTriangleCount() const { return quadCount * 2; }

			/**
			 * @brief Get rendered vertices count.
			 * @return Vertex count.
			*/
			UInt getVertexCount() const { return quadCount * 4; }

			/**
			 * @brief Get index count.
			 * @return Index count.
			*/
			UInt getIndexCount() const { return quadCount * 6; }

			/**
			 * @brief Reset statistics.
			*/
			void reset() { drawCalls = 0; quadCount = 0; }

		};

		/**
		 * @brief Initialize renderer.
		*/
		static void init();

		/**
		 * @brief Begin rendering scene.
		 * @param camera Main camera.
		 * @param transform Main camera transform.
		*/
		static void beginScene(const Camera& camera, const Math::Matrix4x4& transform);

		/**
		 * @brief Begin rendering scene.
		 * @param camera Orthographic camera.
		*/
		static void beginScene(const OrthographicCamera& camera);

		/**
		 * @brief End rendering scene.
		*/
		static void endScene();

		/**
		 * @brief Start a new batch.
		*/
		static void newBatch();

		/**
		 * @brief Flush renderer.
		*/
		static void flush();

		/**
		 * @brief Shutdown renderer.
		*/
		static void shutdown();

		/**
		 * @brief Draw a quad.
		 * @param transform Quad transform.
		 * @param color Quad color.
		*/
		static void drawQuad(const Math::Matrix4x4& transform, const Color& color);

		/**
		 * @brief Draw a quad.
		 * @param transform Quad transform.
		 * @param texture Quad texture.
		 * @param texCoords Quad texture coordinates.
		 * @param tint Quad tint.
		 * @param tiling Quad tiling.
		*/
		static void drawQuad(
			const Math::Matrix4x4& transform, 
			const Reference<Texture2D>& texture, 
			const Quad::TextureCoordinates& texCoords = Quad::DefaultTextureCoords, 
			const Color& tint = Color::white(), 
			const Math::Vector2& tiling = Math::Vector2::one()
		);

		/**
		 * @brief Draw a quad.
		 * @param position Quad position.
		 * @param size Quad size.
		 * @param color Quad color.
		*/
		static void drawQuad(const Math::Vector2& position, const Math::Vector2& size, const Color& color);

		/**
		 * @brief Draw a quad.
		 * @param position Quad position.
		 * @param size Quad size.
		 * @param color Quad color.
		*/
		static void drawQuad(const Math::Vector3& position, const Math::Vector2& size, const Color& color);

		/**
		 * @brief Draw a quad.
		 * @param position Quad position.
		 * @param size Quad size.
		 * @param texture Quad texture.
		 * @param texCoords Quad texture coordinates.
		 * @param tint Quad tint.
		 * @param tiling Quad tiling.
		*/
		static void drawQuad(
			const Math::Vector2& position, 
			const Math::Vector2& size, 
			const Reference<Texture2D>& texture, 
			const Quad::TextureCoordinates& texCoords = Quad::DefaultTextureCoords, 
			const Color& tint = Color::white(), 
			const Math::Vector2& tiling = Math::Vector2::one()
		);

		/**
		 * @brief Draw a quad.
		 * @param position Quad position.
		 * @param size Quad size.
		 * @param texture Quad texture.
		 * @param texCoords Quad texture coordinates.
		 * @param tint Quad tint.
		 * @param tiling Quad tiling.
		*/
		static void drawQuad(
			const Math::Vector3& position, 
			const Math::Vector2& size, 
			const Reference<Texture2D>& texture, 
			const Quad::TextureCoordinates& texCoords = Quad::DefaultTextureCoords, 
			const Color& tint = Color::white(), 
			const Math::Vector2& tiling = Math::Vector2::one()
		);

		/**
		 * @brief Draw a quad.
		 * @param position Quad position.
		 * @param size Quad size.
		 * @param subtexture Quad subtexture.
		 * @param tint Quad tint.
		 * @param tiling Quad tiling.
		*/
		static void drawQuad(
			const Math::Vector2& position, 
			const Math::Vector2& size, 
			const Reference<SubTexture2D>& subtexture, 
			const Color& tint = Color::white(), 
			const Math::Vector2& tiling = Math::Vector2::one()
		);

		/**
		 * @brief Draw a quad.
		 * @param position Quad position.
		 * @param size Quad size.
		 * @param subtexture Quad subtexture.
		 * @param tint Quad tint.
		 * @param tiling Quad tiling.
		*/
		static void drawQuad(
			const Math::Vector3& position, 
			const Math::Vector2& size, 
			const Reference<SubTexture2D>& subtexture, 
			const Color& tint = Color::white(), 
			const Math::Vector2& tiling = Math::Vector2::one()
		);

		/**
		 * @brief Draw a sprite.
		 * @param position Sprite position.
		 * @param size Sprite size.
		 * @param sprite Actual sprite.
		 * @param tint Sprite tint.
		*/
		static void drawSprite(
			const Math::Vector2& position, 
			const Math::Vector2& size, 
			const Reference<Sprite>& sprite, 
			const Color& tint = Color::white()
		);

		/**
		 * @brief Draw a sprite.
		 * @param position Sprite position.
		 * @param size Sprite size.
		 * @param sprite Actual sprite.
		 * @param tint Sprite tint.
		*/
		static void drawSprite(
			const Math::Vector3& position, 
			const Math::Vector2& size, 
			const Reference<Sprite>& sprite, 
			const Color& tint = Color::white()
		);

		/**
		 * @brief Draw a rotated quad.
		 * @param position Quad position.
		 * @param rotation Quad rotation.
		 * @param size Quad size.
		 * @param color Quad color.
		*/
		static void drawRotatedQuad(const Math::Vector2& position, Float rotation, const Math::Vector2& size, const Color& color);

		/**
		 * @brief Draw a rotated quad.
		 * @param position Quad position.
		 * @param rotation Quad rotation.
		 * @param size Quad size.
		 * @param color Quad color.
		*/
		static void drawRotatedQuad(const Math::Vector3& position, Float rotation, const Math::Vector2& size, const Color& color);

		/**
		 * @brief Draw a rotated quad.
		 * @param position Quad position.
		 * @param rotation Quad rotation.
		 * @param size Quad size.
		 * @param texture Quad texture.
		 * @param texCoords Quad texture coordinates.
		 * @param tint Quad tint.
		 * @param tiling Quad tiling.
		*/
		static void drawRotatedQuad(
			const Math::Vector2& position, 
			Float rotation,
			const Math::Vector2& size, 
			const Reference<Texture2D>& texture, 
			const Quad::TextureCoordinates& texCoords = Quad::DefaultTextureCoords, 
			const Color& tint = Color::white(), 
			const Math::Vector2& tiling = Math::Vector2::one()
		);

		/**
		 * @brief Draw a rotated quad.
		 * @param position Quad position.
		 * @param rotation Quad rotation.
		 * @param size Quad size.
		 * @param texture Quad texture.
		 * @param texCoords Quad texture coordinates.
		 * @param tint Quad tint.
		 * @param tiling Quad tiling.
		*/
		static void drawRotatedQuad(
			const Math::Vector3& position, 
			Float rotation,
			const Math::Vector2& size, 
			const Reference<Texture2D>& texture, 
			const Quad::TextureCoordinates& texCoords = Quad::DefaultTextureCoords, 
			const Color& tint = Color::white(), 
			const Math::Vector2& tiling = Math::Vector2::one()
		);

		/**
		 * @brief Draw a rotated quad.
		 * @param position Quad position.
		 * @param rotation Quad rotation.
		 * @param size Quad size.
		 * @param subtexture Quad subtexture.
		 * @param tint Quad tint.
		 * @param tiling Quad tiling.
		*/
		static void drawRotatedQuad(
			const Math::Vector2& position, 
			Float rotation,
			const Math::Vector2& size, 
			const Reference<SubTexture2D>& subtexture, 
			const Color& tint = Color::white(), 
			const Math::Vector2 & tiling = Math::Vector2::one()
		);

		/**
		 * @brief Draw a rotated quad.
		 * @param position Quad position.
		 * @param rotation Quad rotation.
		 * @param size Quad size.
		 * @param subtexture Quad subtexture.
		 * @param tint Quad tint.
		 * @param tiling Quad tiling.
		*/
		static void drawRotatedQuad(
			const Math::Vector3& position, 
			Float rotation,
			const Math::Vector2& size, 
			const Reference<SubTexture2D>& subtexture, 
			const Color& tint = Color::white(), 
			const Math::Vector2& tiling = Math::Vector2::one()
		);

		/**
		 * @brief Draw a rotated sprite.
		 * @param position Sprite position.
		 * @param rotation Sprite rotation.
		 * @param size Sprite size.
		 * @param sprite Actual sprite.
		 * @param tint Sprite tint.
		*/
		static void drawRotatedSprite(
			const Math::Vector2& position, 
			Float rotation,
			const Math::Vector2& size, 
			const Reference<Sprite>& sprite, 
			const Color& tint = Color::white()
		);

		/**
		 * @brief Draw a rotated sprite.
		 * @param position Sprite position.
		 * @param rotation Sprite rotation.
		 * @param size Sprite size.
		 * @param sprite Actual sprite.
		 * @param tint Sprite tint.
		*/
		static void drawRotatedSprite(
			const Math::Vector3& position, 
			Float rotation,
			const Math::Vector2& size, 
			const Reference<Sprite>& sprite, 
			const Color& tint = Color::white()
		);

		// Experimental
		static void drawText(const Math::Vector3& position, const std::string& text, const Reference<FontAtlas>& atlas);

		/**
		 * @brief Reset renderer statistics.
		*/
		static void resetStatistics();

		/**
		 * @brief Get renderer statistics.
		 * @return Render stats.
		*/
		static const Statistics& getStatistics();

		static void beginScreenSpace(); // Exprimental
		static void endScreenSpace(); // Experimental

	private:

		static void flushAndReset();
	};
}
