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

};

struct Renderer2DData {

	const uint32_t MaxQuads = 10000;
	const uint32_t MaxVertices = MaxQuads * 4;
	const uint32_t MaxIndices = MaxQuads * 6;

	uint32_t QuadIndexCount = 0;

	Reference<VertexArray> QuadVertexArray;
	Reference<VertexBuffer> QuadVertexBuffer;
	Reference<Shader> StandardShader;
	Reference<Texture2D> StandardTexture;

	QuadVertex* QuadVertexBufferBase = nullptr;
	QuadVertex* QuadVertexBufferPtr = nullptr;

};

static Renderer2DData s_Data = Renderer2DData();

void Renderer2D::Init()
{
	HNY_PROFILE_FUNCTION();

	s_Data.QuadVertexArray = VertexArray::Create();

	const unsigned int vertexCount = 4;
	const unsigned int bufferStride = 5;
	float vertices[vertexCount * bufferStride] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	};

	s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));

	BufferLayout layout = {
		{ ShaderDataType::Float3, "a_Position" },
		{ ShaderDataType::Float4, "a_Color" },
		{ ShaderDataType::Float2, "a_TexCoord" },
	};

	s_Data.QuadVertexBuffer->SetLayout(layout);
	s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

	s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

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

	Reference<IndexBuffer> _indexBuffer = IndexBuffer::Create(indices, s_Data.MaxIndices);
	s_Data.QuadVertexArray->SetIndexBuffer(_indexBuffer);

	delete[] indices;

	s_Data.StandardTexture = Texture2D::Create(1, 1);
	uint32_t whiteData = 0xFFFFFFFF;
	s_Data.StandardTexture->SetData(&whiteData, sizeof(uint32_t));

	s_Data.StandardShader = Shader::CreateFromFile("assets/shaders/standard2D.glsl");
	s_Data.StandardShader->Bind();
	s_Data.StandardShader->SetInt("u_Texture", 0);
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
	HNY_PROFILE_FUNCTION();

	s_Data.StandardShader->Bind();
	s_Data.StandardShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

	s_Data.QuadIndexCount = 0;
	s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
}

void Renderer2D::EndScene()
{
	HNY_PROFILE_FUNCTION();

	uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
	s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

	Flush();
}

void Renderer2D::Flush()
{
	RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
}

void Renderer2D::Shutdown()
{
	HNY_PROFILE_FUNCTION();
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
	DrawQuad({ position.x, position.y, 1.0f }, size, color);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
	HNY_PROFILE_FUNCTION();

	s_Data.QuadVertexBufferPtr->Position = position;
	s_Data.QuadVertexBufferPtr->Color = color;
	s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
	s_Data.QuadVertexBufferPtr++;
	
	s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, position.z };
	s_Data.QuadVertexBufferPtr->Color = color;
	s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
	s_Data.QuadVertexBufferPtr++;
	
	s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
	s_Data.QuadVertexBufferPtr->Color = color;
	s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
	s_Data.QuadVertexBufferPtr++;
	
	s_Data.QuadVertexBufferPtr->Position = { position.x , position.y + size.y, position.z };
	s_Data.QuadVertexBufferPtr->Color = color;
	s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
	s_Data.QuadVertexBufferPtr++;

	s_Data.QuadIndexCount += 6;

	/*s_Data.StandardShader->SetVec4("u_Color", color);
	s_Data.StandardTexture->Bind();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
		glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	s_Data.StandardShader->SetMat4("u_Transform", transform);

	s_Data.QuadVertexArray->Bind();
	RenderCommand::DrawIndexed(s_Data.QuadVertexArray);*/
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Reference<Texture2D>& texture)
{
	DrawQuad({ position.x, position.y, 1.0f }, size, texture);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Reference<Texture2D>& texture)
{
	HNY_PROFILE_FUNCTION();

	/*s_Data.StandardShader->SetVec4("u_Color", glm::vec4(1.0f));
	texture->Bind();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
		glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	s_Data.StandardShader->SetMat4("u_Transform", transform);

	s_Data.QuadVertexArray->Bind();
	RenderCommand::DrawIndexed(s_Data.QuadVertexArray);*/
}