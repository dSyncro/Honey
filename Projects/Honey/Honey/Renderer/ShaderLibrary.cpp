#include "ShaderLibrary.h"

#include <Honey/Core.h>

using namespace Honey;

void ShaderLibrary::Add(const Reference<Shader>& shader)
{
	const std::string& name = shader->GetName();
	Add(name, shader);
}

void ShaderLibrary::Add(const std::string& name, const Reference<Shader>& shader)
{
	HNY_CORE_ASSERT(!Exists(name), "Shader already exists!");
	_shaders[name] = shader;
}

Reference<Shader> ShaderLibrary::Load(const std::string& path)
{
	Reference<Shader> shader = Shader::CreateFromFile(path);
	Add(shader);
	return shader;
}

Reference<Shader> ShaderLibrary::Load(const std::string& name, const std::string& path)
{
	Reference<Shader> shader = Shader::CreateFromFile(path);
	Add(name, shader);
	return shader;
}

Reference<Shader> ShaderLibrary::Get(const std::string& name)
{
	HNY_CORE_ASSERT(Exists(name), "Shader does not exists!");
	return _shaders[name];
}

bool ShaderLibrary::Exists(const std::string& name) const
{
	return _shaders.find(name) != _shaders.end();
}