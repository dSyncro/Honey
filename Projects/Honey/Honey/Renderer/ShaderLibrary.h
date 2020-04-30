#pragma once

#include <unordered_map>

#include "Shader.h"

namespace Honey {

	class ShaderLibrary {

	public:

		void Add(const Reference<Shader>& shader);
		void Add(const std::string& name, const Reference<Shader>& shader);
		Reference<Shader> Load(const std::string& path);
		Reference<Shader> Load(const std::string& name, const std::string& path);

		Reference<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;

	private:

		std::unordered_map<std::string, Reference<Shader>> _shaders;
	};

}