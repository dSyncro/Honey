#include "Renderer2D.h"

#include <Honey/Core.h>
#include <Honey/Renderer/VertexArray.h>
#include <Honey/Renderer/Shader.h>
#include <Honey/Renderer/RenderCommand.h>

#include <glm/gtc/matrix_transform.hpp>

using namespace Honey;

struct QuadVertex {

	glm::vec3 Position;
	glm::vec4 Color;
	glm::vec2 TexCoord;
	float TextureIndex;

};

struct Renderer2DData {

	const uint32_t MaxQuads = 10000;
	const uint32_t MaxVertices = MaxQuads * 4;
	const uint32_t MaxIndices = MaxQuads * 6;
	static const uint32_t MaxTextureSlots = 32;

	uint32_t QuadIndexCount = 0;

	Reference<VertexArray> QuadVertexArray;
	Reference<VertexBuffer> QuadVertexBuffer;
	Reference<Shader> StandardShader;
	Reference<Texture2D> StandardTexture;

	QuadVertex* QuadVertexBufferBase = nullptr;
	QuadVertex* QuadVertexBufferPtr = nullptr;

	glm::vec4 QuadVertexPositions[4];

	std::array<Reference<Texture2D>, MaxTextureSlots> TextureSlots;
	uint32_t TextureSlotIndex = 1; // White Texture = 0

};

static Renderer2DData s_Data = Renderer2DData();

void Renderer2D::Init()
{
	HNY_PROFILE_FUNCTION();

	// Create Vertex Array
	s_Data.QuadVertexArray = VertexArray::Create();

	// Setup single quad (Renderer2D is quad-based)
	const unsigned int vertexCount = 4;
	const unsigned int bufferStride = 5;
	constexpr float vertices[vertexCount * bufferStride] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	};

	// Create Vertex Buffer
	s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));

	// Set Vertex Buffer Layout
	BufferLayout layout = {
		{ ShaderDataType::Float3, "a_Position" },
		{ ShaderDataType::Float4, "a_Color" },
		{ ShaderDataType::Float2, "a_TexCoord" },
		{ ShaderDataType::Float, "a_TexIndex" },
	};
	s_Data.QuadVertexBuffer->SetLayout(layout);

	// Add Vertex Buffer to Vertex Array
	s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

	// Create Buffer of Vertices
	s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

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
	for (int i = 0; i < s_Data.MaxTextureSlots; i++)
		samplers[i] = i;

	// Setup Shader
	s_Data.StandardShader = Shader::CreateFromFile("assets/shaders/standard2D.glsl");
	s_Data.StandardShader->Bind();
	s_Data.StandardShader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);

	// Initialize First Texture to be Standard Texture
	s_Data.TextureSlots[0] = s_Data.StandardTexture;

	s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
	s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
	s_Data.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
	s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
	HNY_PROFILE_FUNCTION();

	s_Data.StandardShader->Bind();
	s_Data.StandardShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

	s_Data.QuadIndexCount = 0;
	s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

	s_Data.TextureSlotIndex = 1;
}

void Renderer2D::EndScene()
{
	HNY_PROFILE_FUNCTION();

	uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
	s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

	Flush();
}

void Renderer2D::Flush()
{
	// Bind textures
	for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
		s_Data.TextureSlots[i]->Bind(i);

	RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
}

void Renderer2D::Shutdown()
{
	HNY_PROFILE_FUNCTION();

	delete[] s_Data.QuadVertexBufferBase;
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
	DrawQuad({ position.x, position.y, 1.0f }, size, color);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
	HNY_PROFILE_FUNCTION();

	constexpr uint32_t VertexCount = 4;
	constexpr glm::vec2 TextureCoords[VertexCount] = { 
		{ 0.0f, 0.0f }, { 1.0f, 0.0f },
		{ 1.0f, 1.0f }, { 0.0f, 1.0f } 
	};

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	for (uint32_t i = 0; i < VertexCount; i++)
	{
		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = TextureCoords[i];
		s_Data.QuadVertexBufferPtr->TextureIndex = 0;
		s_Data.QuadVertexBufferPtr++;
	}

	s_Data.QuadIndexCount += 6;
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Reference<Texture2D>& texture)
{
	DrawQuad({ position.x, position.y, 1.0f }, size, texture);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Reference<Texture2D>& texture)
{
	HNY_PROFILE_FUNCTION();

	constexpr glm::vec4 white = glm::vec4(1.0f);

	uint32_t slot = 0;
	for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
	{
		if (*texture.get() != *s_Data.TextureSlots[i].get()) continue;

		slot = i;
		break;
	}

	if (!slot)
	{
		slot = s_Data.TextureSlotIndex;
		s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
		s_Data.TextureSlotIndex++;
	}

	constexpr uint32_t VertexCount = 4;
	constexpr glm::vec2 TextureCoords[VertexCount] = {
		{ 0.0f, 0.0f }, { 1.0f, 0.0f },
		{ 1.0f, 1.0f }, { 0.0f, 1.0f }
	};

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	for (uint32_t i = 0; i < VertexCount; i++)
	{
		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
		s_Data.QuadVertexBufferPtr->Color = white;
		s_Data.QuadVertexBufferPtr->TexCoord = TextureCoords[i];
		s_Data.QuadVertexBufferPtr->TextureIndex = slot;
		s_Data.QuadVertexBufferPtr++;
	}

	s_Data.QuadIndexCount += 6;
}