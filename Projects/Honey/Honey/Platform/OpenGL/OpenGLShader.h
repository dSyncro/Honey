#pragma once

#include <string>
#include <unordered_map>

#include <Honey/Renderer/Shader.h>

#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace Honey {

	class OpenGLShader : public Shader {

	public:

		OpenGLShader(const std::string& path);
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void SetUniformInt(const std::string& name, int value);

		void SetUniformFloat(const std::string& name, float value);
		void SetUniformVec2(const std::string& name, const glm::vec2& value);
		void SetUniformVec3(const std::string& name, const glm::vec3& value);
		void SetUniformVec4(const std::string& name, const glm::vec4& value);

		void SetUniformMat3(const std::string& name, const glm::mat3& matrix);
		void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:

		uint32_t _rendererID = 0;

		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

		static std::string OpenGLShader::ReadFile(const std::string& path);
		static std::unordered_map<GLenum, std::string> Process(const std::string& source);
	};

}