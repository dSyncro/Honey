#include "Renderer2D.h"

#include <Honey/Core.h>
#include <Honey/Renderer/Shader.h>
#include <Honey/Renderer/RenderCommand.h>
#include <Honey/Renderer/VertexArray.h>

#include "Quad.h"

using namespace Honey;
using namespace Honey::Math;

struct Renderer2DData {

	static const uint32_t MaxQuads = 10000;
	static const uint32_t MaxVertices = MaxQuads * 4;
	static const uint32_t MaxIndices = MaxQuads * 6;
	static const uint32_t MaxTextureSlots = 32;

	Reference<VertexArray> QuadVertexArray;
	Reference<VertexBuffer> QuadVertexBuffer;
	Reference<Shader> StandardShader;
	Reference<Texture2D> StandardTexture;

	uint32_t QuadIndexCount = 0;
	Quad* QuadBufferBase = nullptr;
	Quad* QuadBufferPtr = nullptr;

	std::array<Reference<Texture2D>, MaxTextureSlots> TextureSlots;
	uint32_t TextureSlotIndex = 1; // White Texture = 0

	Renderer2D::Statistics Stats;
};

static Renderer2DData s_Data = Renderer2DData();

void Renderer2D::Init()
{
	HNY_PROFILE_FUNCTION();

	// Create Vertex Array
	s_Data.QuadVertexArray = VertexArray::Create();

	// Create Vertex Buffer
	s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(Quad::Vertex));

	// Set Vertex Buffer Layout
	s_Data.QuadVertexBuffer->SetLayout({
		{ ShaderDataType::Float3, "a_Position" },
		{ ShaderDataType::Float4, "a_Color" },
		{ ShaderDataType::Float2, "a_TexCoord" },
		{ ShaderDataType::Float, "a_TexIndex" },
		{ ShaderDataType::Float, "a_TilingFactor" },
		}
	);

	// Add Vertex Buffer to Vertex Array
	s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

	// Create Buffer of Quads
	s_Data.QuadBufferBase = new Quad[s_Data.MaxQuads];

	// Setup Indices
	uint32_t* indices = new uint32_t[s_Data.MaxIndices];

	uint32_t offset = 0;
	for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
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
	Reference<IndexBuffer> _indexBuffer = IndexBuffer::Create(indices, s_Data.MaxIndices);
	s_Data.QuadVertexArray->SetIndexBuffer(_indexBuffer);

	delete[] indices; // Free indices

	// Create Special White Texture
	s_Data.StandardTexture = Texture2D::Create(1, 1);
	uint32_t whiteData = 0xFFFFFFFF;
	s_Data.StandardTexture->SetData(&whiteData, sizeof(uint32_t));

	int samplers[s_Data.MaxTextureSlots];
	for (int i = 0; i < s_Data.MaxTextureSlots; i++) samplers[i] = i;

	// Setup Shader
	s_Data.StandardShader = Shader::CreateFromFile("assets/shaders/standard2D.glsl");
	s_Data.StandardShader->Bind();
	s_Data.StandardShader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);

	// Initialize First Texture to be Standard Texture
	s_Data.TextureSlots[0] = s_Data.StandardTexture;
}

void Renderer2D::BeginScene(const Camera& camera, const Matrix4x4& transform)
{
	HNY_PROFILE_FUNCTION();

	s_Data.StandardShader->Bind();
	s_Data.StandardShader->SetMat4("u_ViewProjection", camera.GetProjection() * transform.Inverse());

	NewBatch();
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
	HNY_PROFILE_FUNCTION();

	s_Data.StandardShader->Bind();
	s_Data.StandardShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

	NewBatch();
}

void Renderer2D::EndScene()
{
	HNY_PROFILE_FUNCTION();

	uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadBufferPtr - (uint8_t*)s_Data.QuadBufferBase);
	s_Data.QuadVertexBuffer->SetData(s_Data.QuadBufferBase, dataSize);

	Flush();
}

void Renderer2D::NewBatch()
{
	s_Data.QuadIndexCount = 0;
	s_Data.QuadBufferPtr = s_Data.QuadBufferBase;

	s_Data.TextureSlotIndex = 1;
}

void Renderer2D::Flush()
{
	if (s_Data.QuadIndexCount == 0) return;

	// Bind textures
	for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
		s_Data.TextureSlots[i]->Bind(i);

	RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
	s_Data.Stats.DrawCalls++;
}

void Renderer2D::FlushAndReset()
{
	EndScene();
	NewBatch();
}

void Renderer2D::Shutdown()
{
	HNY_PROFILE_FUNCTION();

	delete[] s_Data.QuadBufferBase;
}

void Renderer2D::DrawQuad(const Matrix4x4& transform, const Vector4& color)
{
	HNY_PROFILE_FUNCTION();

	if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices) FlushAndReset();

	for (uint32_t i = 0; i < Quad::VertexCount; i++)
	{
		Quad::Vertex& vertex = s_Data.QuadBufferPtr->Vertices[i];
		vertex.Set(transform * Quad::VertexPositions[i], color, Quad::TextureCoords[i], 0);
	}
	s_Data.QuadBufferPtr++;
	s_Data.QuadIndexCount += 6;

	s_Data.Stats.QuadCount++;
}

void Renderer2D::DrawQuad(const Matrix4x4& transform, const Reference<Texture2D>& texture, const Vector2& tiling, const Vector4& tint)
{
	HNY_PROFILE_FUNCTION();

	if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices) FlushAndReset();

	uint32_t slot = 0;
	for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
	{
		if (*texture.get() != *s_Data.TextureSlots[i].get()) continue;

		slot = i;
		break;
	}

	if (!slot)
	{
		if (s_Data.TextureSlotIndex >= s_Data.MaxTextureSlots) FlushAndReset();
		slot = s_Data.TextureSlotIndex;
		s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
		s_Data.TextureSlotIndex++;
	}

	for (uint32_t i = 0; i < Quad::VertexCount; i++)
	{
		Quad::Vertex& vertex = s_Data.QuadBufferPtr->Vertices[i];
		vertex.Set(transform * Quad::VertexPositions[i], tint, Quad::TextureCoords[i], (float)slot);
	}
	s_Data.QuadBufferPtr++;

	s_Data.QuadIndexCount += 6;
	s_Data.Stats.QuadCount++;
}

void Renderer2D::DrawQuad(const Vector2& position, const Vector2& size, const Vector4& color)
{
	DrawQuad({ position.X, position.Y, 0.0f }, size, color);
}

void Renderer2D::DrawQuad(const Vector3& position, const Vector2& size, const Vector4& color)
{
	HNY_PROFILE_FUNCTION();

	Matrix4x4 transform = Matrix4x4::Translate(position) * Matrix4x4::Scale({ size.X, size.Y, 1.0f });
	DrawQuad(transform, color);
}

void Renderer2D::DrawQuad(const Vector2& position, const Vector2& size, const Reference<Texture2D>& texture, const Vector2& tiling, const Vector4& tint)
{
	DrawQuad({ position.X, position.Y, 0.0f }, size, texture, tiling, tint);
}

void Renderer2D::DrawQuad(const Vector3& position, const Vector2& size, const Reference<Texture2D>& texture, const Vector2& tiling, const Vector4& tint)
{
	HNY_PROFILE_FUNCTION();

	Matrix4x4 transform = Matrix4x4::Translate(position) * Matrix4x4::Scale({ size.X, size.Y, 1.0f });
	DrawQuad(transform, texture, tiling, tint);
}

void Renderer2D::DrawRotatedQuad(const Vector2& position, float rotation, const Vector2& size, const Reference<Texture2D>& texture, const Vector2& tiling, const Vector4& tint)
{
	DrawRotatedQuad({ position.X, position.Y, 0.0f }, rotation, size, texture, tiling, tint);
}

void Renderer2D::DrawRotatedQuad(const Vector3& position, float rotation, const Vector2& size, const Reference<Texture2D>& texture, const Vector2& tiling, const Vector4& tint)
{
	HNY_PROFILE_FUNCTION();

	Matrix4x4 transform = Matrix4x4::Translate(position)
		* Matrix4x4::Rotate(rotation * Mathf::Degrees2Radians, { 0.0f, 0.0f, 1.0f })
		* Matrix4x4::Scale({ size.X, size.Y, 1.0f });

	DrawQuad(transform, texture, tiling, tint);
}

void Renderer2D::ResetStatistics()
{
	s_Data.Stats.Reset();
}

const Renderer2D::Statistics& Renderer2D::GetStatistics() { return s_Data.Stats; }
