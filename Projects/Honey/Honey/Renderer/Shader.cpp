#include "Shader.h"

#include <Honey/Core.h>

#include <Honey/Renderer/Renderer.h>
#include <Honey/Platform/OpenGL/OpenGLShader.h>

using namespace Honey;

Reference<Shader> Shader::CreateFromFile(const std::string& path)
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None: HNY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return OpenGLShader::FromFile(path);
	}

	HNY_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}


Reference<Shader> Shader::CreateFromSource(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None: HNY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return OpenGLShader::FromSource(name, vertexSource, fragmentSource);
	}

	HNY_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
