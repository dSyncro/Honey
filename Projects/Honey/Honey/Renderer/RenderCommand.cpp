#include "RenderCommand.h"

#include <Honey/Platform/OpenGL/OpenGLRendererAPI.h>

using namespace Honey;

Unique<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::create();

void RenderCommand::init()
{
	s_RendererAPI->init();
}

void RenderCommand::setViewport(Math::Vector2 location, Math::Vector2 size)
{
	s_RendererAPI->setViewport(location, size);
}

void RenderCommand::setViewport(UInt x, UInt y, UInt width, UInt height)
{
	s_RendererAPI->setViewport(x, y, width, height);
}

void RenderCommand::drawIndexed(const Reference<VertexArray>& vertexArray, UInt indexCount)
{
	s_RendererAPI->drawIndexed(vertexArray);
}
