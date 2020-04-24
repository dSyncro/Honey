#include "RenderCommand.h"

#include <Honey/Platform/OpenGL/OpenGLRendererAPI.h>

using namespace Honey;

RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

void RenderCommand::Init()
{
	s_RendererAPI->Init();
}