#include "Shader.h"

#include <Honey/Core.h>

#include <Honey/Renderer/Renderer.h>
#include <Honey/Platform/OpenGL/OpenGLShader.h>

using namespace Honey;

Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None: HNY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSource, fragmentSource);
	}

	HNY_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
