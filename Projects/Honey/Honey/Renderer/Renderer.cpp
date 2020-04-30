#include "Renderer.h"

#include <Honey/Platform/OpenGL/OpenGLShader.h>

using namespace Honey;

Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

void Renderer::Init()
{
	RenderCommand::Init();
}

void Renderer::BeginScene(OrthographicCamera& camera)
{
	s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene()
{

}

void Renderer::Submit(const Reference<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
{
	shader->Bind();
	std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
	std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_Transform", transform);

	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
	RenderCommand::SetViewport(0, 0, width, height);
}
