#include "Renderer.h"

#include <Honey/Platform/OpenGL/OpenGLShader.h>
#include <Honey/Renderer/2D/Renderer2D.h>

using namespace Honey;
using namespace Honey::Math;

Unique<Renderer::SceneData> Renderer::s_SceneData = CreateUnique<Renderer::SceneData>();

void Renderer::init()
{
	HNY_PROFILE_FUNCTION();

	RenderCommand::init();
	Renderer2D::init();
}

void Renderer::shutdown()
{
	HNY_PROFILE_FUNCTION();

	Renderer2D::shutdown();
}

void Renderer::beginScene(OrthographicCamera& camera)
{
	s_SceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
}

void Renderer::endScene()
{

}

void Renderer::submit(const Reference<Shader>& shader, const Reference<VertexArray>& vertexArray, const Matrix4x4& transform)
{
	shader->bind();
	shader->setMat4("u_ViewProjection", s_SceneData->viewProjectionMatrix);
	shader->setMat4("u_Transform", transform);

	vertexArray->bind();
	RenderCommand::drawIndexed(vertexArray);
}

void Renderer::onWindowResize(UInt width, UInt height)
{
	RenderCommand::setViewport(0, 0, width, height);
}
