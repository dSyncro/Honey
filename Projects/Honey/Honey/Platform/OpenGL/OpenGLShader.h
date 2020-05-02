#pragma once

#include <string>
#include <unordered_map>

#include <Honey/Renderer/Shader.h>

#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace Honey {

	class OpenGLShader final : public Shader {

	public:

		OpenGLShader(const std::string& name, const std::unordered_map<GLenum, std::string>& shaders);

		static Reference<OpenGLShader> FromFile(const std::string& path);
		static Reference<OpenGLShader> FromSource(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);

		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::string& GetName() const override { return _name; }

		virtual void SetInt(const std::string& name, int value) override;

		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetVec2(const std::string& name, const glm::vec2& value) override;
		virtual void SetVec3(const std::string& name, const glm::vec3& value) override;
		virtual void SetVec4(const std::string& name, const glm::vec4& value) override;

		virtual void SetMat2(const std::string& name, const glm::mat2& matrix) override;
		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override;

	private:

		uint32_t _rendererID = 0;
		std::string _name;

		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

		static std::string OpenGLShader::ReadFile(const std::string& path);
		static std::unordered_map<GLenum, std::string> Process(const std::string& source);
	};

}