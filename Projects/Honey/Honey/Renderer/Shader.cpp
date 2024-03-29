#include "Shader.h"

#include <Honey/Core.h>

#include <Honey/Renderer/Renderer.h>
#include <Honey/Platform/OpenGL/OpenGLShader.h>

using namespace Honey;

Reference<Shader> Shader::createFromFile(const std::string& path)
{
	switch (Renderer::getAPI())
	{
		case RendererAPI::API::None: HNY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return OpenGLShader::fromFile(path);
		case RendererAPI::API::DirectX: HNY_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported!"); return nullptr;
	}

	HNY_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}


Reference<Shader> Shader::createFromSource(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
{
	switch (Renderer::getAPI())
	{
		case RendererAPI::API::None: HNY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return OpenGLShader::fromSource(name, vertexSource, fragmentSource);
		case RendererAPI::API::DirectX: HNY_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported!"); return nullptr;
	}

	HNY_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
