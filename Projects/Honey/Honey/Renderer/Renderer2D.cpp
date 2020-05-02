#include "Renderer2D.h"

#include <Honey/Core.h>
#include <Honey/Renderer/VertexArray.h>
#include <Honey/Renderer/Shader.h>
#include <Honey/Renderer/RenderCommand.h>

#include <glm/gtc/matrix_transform.hpp>

using namespace Honey;

struct Renderer2DStorage {

	Reference<VertexArray> QuadVertexArray;
	Reference<Shader> ColorShader;
	Reference<Shader> TextureShader;

};

static Renderer2DStorage* s_Data;

void Renderer2D::Init()
{
	s_Data = new Renderer2DStorage();

	s_Data->QuadVertexArray = VertexArray::Create();

	const unsigned int vertexCount = 4;
	const unsigned int bufferStride = 5;
	float vertices[vertexCount * bufferStride] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	};

	Reference<VertexBuffer> _vertexBuffer;
	_vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

	BufferLayout layout = {
		{ ShaderDataType::Float3, "a_Position" },
		{ ShaderDataType::Float2, "a_TexCoord" },
	};

	_vertexBuffer->SetLayout(layout);
	s_Data->QuadVertexArray->AddVertexBuffer(_vertexBuffer);

	unsigned int indices[3 * 2] = { 0, 1, 2, 2, 3, 0 };

	Reference<IndexBuffer> _indexBuffer;
	_indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));
	s_Data->QuadVertexArray->SetIndexBuffer(_indexBuffer);

	s_Data->ColorShader = Shader::CreateFromFile("assets/shaders/color.glsl");
	s_Data->TextureShader = Shader::CreateFromFile("assets/shaders/texture.glsl");
	s_Data->TextureShader->Bind();
	s_Data->TextureShader->SetInt("u_Texture", 0);
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
	s_Data->ColorShader->Bind();
	s_Data->ColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

	s_Data->TextureShader->Bind();
	s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
}

void Renderer2D::EndScene()
{

}

void Renderer2D::Shutdown()
{
	delete s_Data;
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
	DrawQuad({ position.x, position.y, 1.0f }, size, color);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
	s_Data->ColorShader->Bind();
	s_Data->ColorShader->SetVec4("u_Color", color);

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
		glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	s_Data->ColorShader->SetMat4("u_Transform", transform);

	s_Data->QuadVertexArray->Bind();
	RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Reference<Texture2D>& texture)
{
	DrawQuad({ position.x, position.y, 1.0f }, size, texture);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Reference<Texture2D>& texture)
{
	s_Data->TextureShader->Bind();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
		glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	s_Data->TextureShader->SetMat4("u_Transform", transform);

	texture->Bind();
	s_Data->QuadVertexArray->Bind();
	RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
}