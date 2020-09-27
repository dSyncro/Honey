#include "Renderer.h"

#include <Honey/Platform/OpenGL/OpenGLShader.h>
#include <Honey/Renderer/2D/Renderer2D.h>

using namespace Honey;
using namespace Honey::Math;

Unique<Renderer::SceneData> Renderer::s_SceneData = CreateUnique<Renderer::SceneData>();

void Renderer::Init()
{
	HNY_PROFILE_FUNCTION();

	RenderCommand::Init();
	Renderer2D::Init();
}

void Renderer::Shutdown()
{
	HNY_PROFILE_FUNCTION();

	Renderer2D::Shutdown();
}

void Renderer::BeginScene(OrthographicCamera& camera)
{
	s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene()
{

}

void Renderer::Submit(const Reference<Shader>& shader, const Reference<VertexArray>& vertexArray, const Matrix4x4& transform)
{
	shader->bind();
	shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
	shader->SetMat4("u_Transform", transform);

	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
	RenderCommand::SetViewport(0, 0, width, height);
}
