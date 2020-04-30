#pragma once

#include <string>

#include <Honey/Core.h>

namespace Honey {

	class Shader {

	public:

		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::string& GetName() const = 0;

		static Reference<Shader> CreateFromFile(const std::string& path);
		static Reference<Shader> CreateFromSource(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
	};

}