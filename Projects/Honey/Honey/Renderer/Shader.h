#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Honey {

	class Shader {

	public:

		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:

		uint32_t _rendererID = 0;
	};

}