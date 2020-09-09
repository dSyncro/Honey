#pragma once

#include "Quad.h"

#include <Honey/Math/Vectors.h>
#include <Honey/Math/Matrix/Matrix4x4.h>
#include <Honey/Renderer/Camera/Camera.h>
#include <Honey/Renderer/Camera/OrthographicCamera.h>
#include <Honey/Renderer/2D/Sprite.h>
#include <Honey/Renderer/2D/UI/Text/FontAtlas.h>

namespace Honey {

	class Renderer2D {

	public:

		Renderer2D() = delete;
		Renderer2D(const Renderer2D&) = delete;
		Renderer2D& operator =(const Renderer2D&) = delete;

		struct Statistics {

			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTriangleCount() const { return QuadCount * 2; }
			uint32_t GetVertexCount() const { return QuadCount * 4; }
			uint32_t GetIndexCount() const { return QuadCount * 6; }

			void Reset() { DrawCalls = 0; QuadCount = 0; }

		};

		static void Init();

		static void BeginScene(const Camera& camera, const Math::Matrix4x4& transform);
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void NewBatch();
		static void Flush();

		static void Shutdown();

		static void DrawQuad(const Math::Matrix4x4& transform, const Color& color);
		static void DrawQuad(const Math::Matrix4x4& transform, const Reference<Texture2D>& texture, const Quad::TextureCoordinates& texCoords = Quad::DefaultTextureCoords, const Math::Vector4& tint = Math::Vector4::One, const Math::Vector2& tiling = Math::Vector2::One);

		static void DrawQuad(const Math::Vector2& position, const Math::Vector2& size, const Color& color);
		static void DrawQuad(const Math::Vector3& position, const Math::Vector2& size, const Color& color);
		static void DrawQuad(const Math::Vector2& position, const Math::Vector2& size, const Reference<Texture2D>& texture, const Quad::TextureCoordinates& texCoords = Quad::DefaultTextureCoords, const Color& tint = Color::White, const Math::Vector2& tiling = Math::Vector2::One);
		static void DrawQuad(const Math::Vector3& position, const Math::Vector2& size, const Reference<Texture2D>& texture, const Quad::TextureCoordinates& texCoords = Quad::DefaultTextureCoords, const Color& tint = Color::White, const Math::Vector2& tiling = Math::Vector2::One);
		static void DrawQuad(const Math::Vector2& position, const Math::Vector2& size, const Reference<SubTexture2D>& subtexture, const Color& tint = Color::White, const Math::Vector2& tiling = Math::Vector2::One);
		static void DrawQuad(const Math::Vector3& position, const Math::Vector2& size, const Reference<SubTexture2D>& subtexture, const Color& tint = Color::White, const Math::Vector2& tiling = Math::Vector2::One);
		static void DrawSprite(const Math::Vector2& position, const Math::Vector2& size, const Reference<Sprite>& sprite, const Color& tint = Color::White);
		static void DrawSprite(const Math::Vector3& position, const Math::Vector2& size, const Reference<Sprite>& sprite, const Color& tint = Color::White);

		static void DrawRotatedQuad(const Math::Vector2& position, float rotation, const Math::Vector2& size, const Color& color);
		static void DrawRotatedQuad(const Math::Vector3& position, float rotation, const Math::Vector2& size, const Color& color);
		static void DrawRotatedQuad(const Math::Vector2& position, float rotation, const Math::Vector2& size, const Reference<Texture2D>& texture, const Quad::TextureCoordinates& texCoords = Quad::DefaultTextureCoords, const Color& tint = Color::White, const Math::Vector2& tiling = Math::Vector2::One);
		static void DrawRotatedQuad(const Math::Vector3& position, float rotation, const Math::Vector2& size, const Reference<Texture2D>& texture, const Quad::TextureCoordinates& texCoords = Quad::DefaultTextureCoords, const Color& tint = Color::White, const Math::Vector2& tiling = Math::Vector2::One);
		static void DrawRotatedQuad(const Math::Vector2& position, float rotation, const Math::Vector2& size, const Reference<SubTexture2D>& subtexture, const Color& tint = Color::White, const Math::Vector2 & tiling = Math::Vector2::One);
		static void DrawRotatedQuad(const Math::Vector3& position, float rotation, const Math::Vector2& size, const Reference<SubTexture2D>& subtexture, const Color& tint = Color::White, const Math::Vector2& tiling = Math::Vector2::One);
		static void DrawRotatedSprite(const Math::Vector2& position, float rotation, const Math::Vector2& size, const Reference<Sprite>& sprite, const Color& tint = Color::White);
		static void DrawRotatedSprite(const Math::Vector3& position, float rotation, const Math::Vector2& size, const Reference<Sprite>& sprite, const Color& tint = Color::White);

		static void DrawText(const Math::Vector3& position, const std::string& text, const Reference<FontAtlas>& atlas);

		static void ResetStatistics();
		static const Statistics& GetStatistics();

	private:

		static void FlushAndReset();
	};
}
