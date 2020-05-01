#include "RenderCommand.h"

#include <Honey/Platform/OpenGL/OpenGLRendererAPI.h>

using namespace Honey;

Unique<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

void RenderCommand::Init()
{
	s_RendererAPI->Init();
}