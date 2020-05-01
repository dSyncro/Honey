#include "Renderer2D.h"

#include <Honey/Core.h>
#include <Honey/Renderer/VertexArray.h>
#include <Honey/Renderer/Shader.h>
#include <Honey/Renderer/RenderCommand.h>

#include <Honey/Platform/OpenGL/OpenGLShader.h>

using namespace Honey;

struct Renderer2DStorage {

	Reference<VertexArray> QuadVertexArray;
	Reference<Shader> ColorShader;

};

static Renderer2DStorage* s_Data;

void Renderer2D::Init()
{
	s_Data = new Renderer2DStorage();

	s_Data->QuadVertexArray = VertexArray::Create();

	const unsigned int vertexCount = 4;
	const unsigned int bufferStride = 3;
	float vertices[vertexCount * bufferStride] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};

	Reference<VertexBuffer> _vertexBuffer;
	_vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

	BufferLayout layout = {
		{ ShaderDataType::Float3, "a_Position" },
	};

	_vertexBuffer->SetLayout(layout);
	s_Data->QuadVertexArray->AddVertexBuffer(_vertexBuffer);

	unsigned int indices[3 * 2] = { 0, 1, 2, 2, 3, 0 };

	Reference<IndexBuffer> _indexBuffer;
	_indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));
	s_Data->QuadVertexArray->SetIndexBuffer(_indexBuffer);

	s_Data->ColorShader = Shader::CreateFromFile("assets/shaders/color.glsl");
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
	s_Data->ColorShader->Bind();
	std::dynamic_pointer_cast<OpenGLShader>(s_Data->ColorShader)->SetUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	std::dynamic_pointer_cast<OpenGLShader>(s_Data->ColorShader)->SetUniformMat4("u_Transform", glm::mat4(1.0f));
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
	std::dynamic_pointer_cast<OpenGLShader>(s_Data->ColorShader)->SetUniformVec4("u_Color", color);

	s_Data->QuadVertexArray->Bind();
	RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
}