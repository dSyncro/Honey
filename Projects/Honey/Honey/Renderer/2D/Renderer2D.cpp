#include "Renderer2D.h"

#include <Honey/Core.h>
#include <Honey/Renderer/Shader.h>
#include <Honey/Renderer/RenderCommand.h>
#include <Honey/Renderer/VertexArray.h>

using namespace Honey;
using namespace Honey::Math;

struct Renderer2DData {

	static const UInt maxQuads = 10000;
	static const UInt maxVertices = maxQuads * 4;
	static const UInt maxIndices = maxQuads * 6;
	static const UInt maxTextureSlots = 32; // TODO: Query for max texture slots

	Reference<VertexArray> quadVertexArray;
	Reference<VertexBuffer> quadVertexBuffer;
	Reference<Shader> standardShader;
	Reference<Texture2D> standardTexture;

	uint32_t quadIndexCount = 0;

	// Actual quad buffer
	Quad* quadBufferBase = nullptr;

	// At which point in buffer we are?
	Quad* quadBufferPtr = nullptr;

	std::array<Reference<Texture2D>, maxTextureSlots> textureSlots;
	UInt textureSlotIndex = 1; // White Texture = 0

	Renderer2D::Statistics stats;
};

static Renderer2DData s_Data = Renderer2DData();

static Math::Matrix4x4 WorldMatrix;
static Reference<Shader> TextShader;

void Renderer2D::init()
{
	HNY_PROFILE_FUNCTION();

	// Create Vertex Array
	s_Data.quadVertexArray = VertexArray::create();

	// Create Vertex Buffer
	s_Data.quadVertexBuffer = VertexBuffer::create(s_Data.maxVertices * sizeof(Quad::Vertex));

	// Set Vertex Buffer Layout
	s_Data.quadVertexBuffer->setLayout({
		{ ShaderDataType::Vector3, "a_Position" },
		{ ShaderDataType::Vector4, "a_Color" },
		{ ShaderDataType::Vector2, "a_TexCoord" },
		{ ShaderDataType::Float, "a_TexIndex" },
		{ ShaderDataType::Vector2, "a_Tiling" },
		}
	);

	// Add Vertex Buffer to Vertex Array
	s_Data.quadVertexArray->addVertexBuffer(s_Data.quadVertexBuffer);

	// Create Buffer of Quads
	s_Data.quadBufferBase = new Quad[s_Data.maxQuads];

	// Setup Indices
	UInt* indices = new UInt[s_Data.maxIndices];

	UInt offset = 0;
	for (UInt i = 0; i < s_Data.maxIndices; i += 6)
	{
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

	// Create Index Buffer
	Reference<IndexBuffer> _indexBuffer = IndexBuffer::create(indices, s_Data.maxIndices);
	s_Data.quadVertexArray->setIndexBuffer(_indexBuffer);

	delete[] indices; // Free indices

	// Create Special White Texture
	s_Data.standardTexture = Texture2D::create(1, 1);
	UInt whiteData = 0xFFFFFFFF;
	s_Data.standardTexture->setData(&whiteData, sizeof(UInt));

	int samplers[s_Data.maxTextureSlots];
	for (int i = 0; i < s_Data.maxTextureSlots; i++) samplers[i] = i;

	// Setup Shader
	s_Data.standardShader = Shader::createFromFile("assets/shaders/standard2D.glsl");
	s_Data.standardShader->bind();
	s_Data.standardShader->setIntArray("u_Textures", samplers, s_Data.maxTextureSlots);
	TextShader = Shader::createFromFile("assets/shaders/text.glsl");
	TextShader->bind();
	TextShader->setIntArray("u_Textures", samplers, s_Data.maxTextureSlots);

	// Initialize First Texture to be Standard Texture
	s_Data.textureSlots[0] = s_Data.standardTexture;
}

void Renderer2D::beginScene(const Camera& camera, const Matrix4x4& transform)
{
	HNY_PROFILE_FUNCTION();

	WorldMatrix = camera.getProjection() * transform.inverse();

	s_Data.standardShader->bind();
	s_Data.standardShader->setMat4("u_ViewProjection", camera.getProjection() * transform.inverse());

	newBatch();
}

void Renderer2D::beginScene(const OrthographicCamera& camera)
{
	HNY_PROFILE_FUNCTION();
	s_Data.standardShader->setMat4("u_ViewProjection", camera.getViewProjectionMatrix());

	newBatch();
}

void Renderer2D::endScene()
{
	HNY_PROFILE_FUNCTION();

	UInt dataSize = static_cast<UInt>((Byte*)s_Data.quadBufferPtr - (Byte*)s_Data.quadBufferBase);
	s_Data.quadVertexBuffer->setData(s_Data.quadBufferBase, dataSize);

	flush();
}

void Renderer2D::newBatch()
{
	s_Data.quadIndexCount = 0;
	s_Data.quadBufferPtr = s_Data.quadBufferBase;

	s_Data.textureSlotIndex = 1;
}

void Renderer2D::flush()
{
	if (s_Data.quadIndexCount == 0) return;

	// Bind textures
	for (UInt i = 0; i < s_Data.textureSlotIndex; i++)
		s_Data.textureSlots[i]->bindToSlot(i);

	RenderCommand::drawIndexed(s_Data.quadVertexArray, s_Data.quadIndexCount);
	s_Data.stats.drawCalls++;
}

void Renderer2D::flushAndReset()
{
	endScene();
	newBatch();
}

void Renderer2D::shutdown()
{
	HNY_PROFILE_FUNCTION();

	delete[] s_Data.quadBufferBase;
}

void Renderer2D::drawQuad(const Matrix4x4& transform, const Color& color)
{
	HNY_PROFILE_FUNCTION();

	if (s_Data.quadIndexCount >= Renderer2DData::maxIndices) flushAndReset();

	for (UInt i = 0; i < Quad::VertexCount; i++)
	{
		Quad::Vertex& vertex = s_Data.quadBufferPtr->Vertices[i];
		vertex.Set(transform * Quad::VertexPositions[i], color, Quad::DefaultTextureCoords[i], 0);
	}
	s_Data.quadBufferPtr++;
	s_Data.quadIndexCount += 6;

	s_Data.stats.quadCount++;
}

void Renderer2D::drawQuad(
	const Matrix4x4& transform, 
	const Reference<Texture2D>& texture, 
	const Quad::TextureCoordinates& texCoords, 
	const Color& tint, const Vector2& tiling)
{
	HNY_PROFILE_FUNCTION();

	// If no texture fallback to color only version
	if (!texture) return drawQuad(transform, tint);

	if (s_Data.quadIndexCount >= Renderer2DData::maxIndices) flushAndReset();

	int slot = 0;
	for (int i = 1; i < static_cast<int>(s_Data.textureSlotIndex); i++)
	{
		if (*texture != *s_Data.textureSlots[i]) continue;

		slot = i;
		break;
	}

	if (!slot)
	{
		if (s_Data.textureSlotIndex >= s_Data.maxTextureSlots) flushAndReset();
		slot = s_Data.textureSlotIndex;
		s_Data.textureSlots[slot] = texture;
		s_Data.textureSlotIndex++;
	}

	for (UInt i = 0; i < Quad::VertexCount; i++)
	{
		Quad::Vertex& vertex = s_Data.quadBufferPtr->Vertices[i];
		vertex.Set(transform * Quad::VertexPositions[i], tint, texCoords[i], slot);
	}
	s_Data.quadBufferPtr++;

	s_Data.quadIndexCount += 6;
	s_Data.stats.quadCount++;
}

void Renderer2D::drawQuad(const Vector2& position, const Vector2& size, const Color& color)
{
	drawQuad({ position.x, position.y, 0.0f }, size, color);
}

void Renderer2D::drawQuad(const Vector3& position, const Vector2& size, const Color& color)
{
	HNY_PROFILE_FUNCTION();

	Matrix4x4 transform = Matrix4x4::translate(position) * Matrix4x4::scale({ size.x, size.y, 1.0f });
	drawQuad(transform, color);
}

void Renderer2D::drawQuad(
	const Vector2& position, 
	const Vector2& size, 
	const Reference<Texture2D>& texture, 
	const Quad::TextureCoordinates& texCoords, 
	const Color& tint, const Vector2& tiling)
{
	drawQuad({ position.x, position.y, 0.0f }, size, texture, texCoords, tint, tiling);
}

void Renderer2D::drawQuad(
	const Vector3& position, 
	const Vector2& size, 
	const Reference<Texture2D>& texture, 
	const Quad::TextureCoordinates& texCoords, 
	const Color& tint, const Vector2& tiling)
{
	HNY_PROFILE_FUNCTION();

	Matrix4x4 transform = Matrix4x4::translate(position) * Matrix4x4::scale({ size.x, size.y, 1.0f });
	drawQuad(transform, texture, texCoords, tint, tiling);
}

void Renderer2D::drawQuad(
	const Vector2& position, 
	const Vector2& size, 
	const Reference<SubTexture2D>& subtexture, 
	const Color& tint, const Vector2& tiling)
{
	drawQuad({ position.x, position.y, 0.0f }, size, subtexture, tint, tiling);
}

void Renderer2D::drawQuad(
	const Vector3& position, 
	const Vector2& size, 
	const Reference<SubTexture2D>& subtexture, 
	const Color& tint, const Vector2& tiling)
{
	HNY_PROFILE_FUNCTION();

	const Reference<Texture2D>& texture = subtexture->getTexture();
	const Quad::TextureCoordinates& texCoords = subtexture->getTextureCoords();

	Matrix4x4 transform = Matrix4x4::translate(position) * Matrix4x4::scale({ size.x, size.y, 1.0f });
	drawQuad(transform, texture, texCoords, tint, tiling);
}

void Renderer2D::drawSprite(const Math::Vector2& position, const Math::Vector2& size, const Reference<Sprite>& sprite, const Color& tint)
{
	drawSprite({ position.x, position.y, 0.0f }, size, sprite, tint);
}

void Renderer2D::drawSprite(const Math::Vector3& position, const Math::Vector2& size, const Reference<Sprite>& sprite, const Color& tint)
{
	HNY_PROFILE_FUNCTION();

	Matrix4x4 transform = Matrix4x4::translate(position)
		* Matrix4x4::scale({ size.x, size.y, 1.0f });

	// If no sprite fallback to color only version
	if (!sprite) return drawQuad(transform, tint);

	drawQuad(transform, sprite->texture, sprite->uv, tint);
}

void Renderer2D::drawRotatedQuad(const Vector2& position, Float rotation, const Vector2& size, const Color& color)
{
	drawRotatedQuad({ position.x, position.y, 0.0f }, rotation, size, color);
}

void Renderer2D::drawRotatedQuad(const Vector3& position, Float rotation, const Math::Vector2& size, const Color& color)
{
	HNY_PROFILE_FUNCTION();

	Matrix4x4 transform = Matrix4x4::translate(position)
		* Matrix4x4::rotate(rotation * Mathf::degrees2Radians(), Vector3::forward())
		* Matrix4x4::scale({ size.x, size.y, 1.0f });

	drawQuad(transform, color);
}

void Renderer2D::drawRotatedQuad(
	const Vector2& position, 
	Float rotation, 
	const Vector2& size, 
	const Reference<Texture2D>& texture, 
	const Quad::TextureCoordinates& texCoords, 
	const Color& tint, const Vector2& tiling)
{
	drawRotatedQuad({ position.x, position.y, 0.0f }, rotation, size, texture, texCoords, tint, tiling);
}

void Renderer2D::drawRotatedQuad(
	const Vector3& position, 
	Float rotation, 
	const Vector2& size, 
	const Reference<Texture2D>& texture, 
	const Quad::TextureCoordinates& texCoords, 
	const Color& tint, const Vector2& tiling)
{
	HNY_PROFILE_FUNCTION();

	Matrix4x4 transform = Matrix4x4::translate(position)
		* Matrix4x4::rotate(rotation * Mathf::degrees2Radians(), Vector3::forward())
		* Matrix4x4::scale({ size.x, size.y, 1.0f });

	drawQuad(transform, texture, texCoords, tint, tiling);
}

void Renderer2D::drawRotatedQuad(
	const Vector2& position, 
	Float rotation, 
	const Vector2& size, 
	const Reference<SubTexture2D>& subtexture, 
	const Color& tint, const Vector2& tiling)
{
	drawRotatedQuad({ position.x, position.y, 1.0f }, rotation, size, subtexture, tint, tiling);
}

void Renderer2D::drawRotatedQuad(
	const Vector3& position, 
	Float rotation, 
	const Vector2& size, 
	const Reference<SubTexture2D>& subtexture,
	const Color& tint, const Vector2& tiling)
{
	HNY_PROFILE_FUNCTION();

	const Reference<Texture2D>& texture = subtexture->getTexture();
	const Quad::TextureCoordinates& texCoords = subtexture->getTextureCoords();

	Matrix4x4 transform = Matrix4x4::translate(position)
		* Matrix4x4::rotate(rotation * Mathf::degrees2Radians(), Vector3::forward())
		* Matrix4x4::scale({ size.x, size.y, 1.0f });

	drawQuad(transform, texture, texCoords, tint, tiling);
}

void Renderer2D::drawRotatedSprite(const Vector2& position, Float rotation, const Vector2& size, const Reference<Sprite>& sprite, const Color& tint)
{
	drawRotatedSprite({ position.x, position.y, 0.0f }, rotation, size, sprite, tint);
}

void Renderer2D::drawRotatedSprite(const Vector3& position, Float rotation, const Vector2& size, const Reference<Sprite>& sprite, const Color& tint)
{
	HNY_PROFILE_FUNCTION();

	Matrix4x4 transform = Matrix4x4::translate(position)
		* Matrix4x4::rotate(rotation * Mathf::degrees2Radians(), Vector3::forward())
		* Matrix4x4::scale({ size.x, size.y, 1.0f });

	// If no sprite fallback to color only version
	if (!sprite) return drawQuad(transform, tint);

	drawQuad(transform, sprite->texture, sprite->uv, tint);
}

void Renderer2D::drawText(const Vector3& position, const std::string& text, const Reference<FontAtlas>& atlas)
{
	const Reference<Texture2D>& texture = atlas->getTexture();

	Float currentPoint = 0.0f;
	Float baseline = atlas->getScaledAscent();
	drawQuad(Vector2(0, baseline), Vector2(2000, 1), Color::yellow());
	for (std::size_t i = 0; i < text.length(); i++)
	{
		Int kerning = 0;
		if (i + 1 < text.length())
			kerning = atlas->getFont()->getKerning(text[i], text[i + 1]) 
			* Mathf::roundToInt(atlas->getScaleFactor());

		const Glyph& glyph = atlas->getGlyph(text[i]);

		Vector2 quadPosition = Vector2(currentPoint + kerning, baseline) + glyph.offset + (Vector2)position;
		Vector2 quadScale = (Vector2Int)glyph.boundingBox.getSize();

		currentPoint += glyph.advance;
		drawQuad(quadPosition, quadScale, texture, glyph.uv, Color::white());
	}
}

void Renderer2D::beginScreenSpace()
{
	flushAndReset();

	const Matrix4x4 screenSpace = Matrix4x4::orthographic(0, 800, 600, 0, -1.0f, 1.0f);
	TextShader->setMat4("u_ViewProjection", screenSpace);
}

void Renderer2D::endScreenSpace()
{
	flushAndReset();
	s_Data.standardShader->setMat4("u_ViewProjection", WorldMatrix);
}


void Renderer2D::resetStatistics()
{
	s_Data.stats.reset();
}

const Renderer2D::Statistics& Renderer2D::getStatistics() { return s_Data.stats; }
