#include "ShaderLibrary.h"

#include <Honey/Core.h>

using namespace Honey;

void ShaderLibrary::add(const Reference<Shader>& shader)
{
	// Just use default shader name

	const std::string& name = shader->getName();
	add(name, shader);
}

void ShaderLibrary::add(const std::string& name, const Reference<Shader>& shader)
{
	// TODO: improve this code.

	HNY_CORE_ASSERT(!exists(name), "Shader already exists!");
	_shaders[name] = shader;
}

Reference<Shader> ShaderLibrary::load(const std::string& path)
{
	Reference<Shader> shader = Shader::createFromFile(path);
	add(shader);
	return shader;
}

Reference<Shader> ShaderLibrary::load(const std::string& name, const std::string& path)
{
	Reference<Shader> shader = Shader::createFromFile(path);
	add(name, shader);
	return shader;
}

Reference<Shader> ShaderLibrary::get(const std::string& name)
{
	HNY_CORE_ASSERT(exists(name), "Shader does not exists!");
	return _shaders[name];
}

bool ShaderLibrary::exists(const std::string& name) const
{
	return _shaders.find(name) != _shaders.end();
}
