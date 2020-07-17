#pragma once

#include <string>

#include <Honey/Core/MemoryManagement.h>

#include <glm/glm.hpp>

namespace Honey {

	class Shader {

	public:

		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;

		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetVec2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetVec3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetVec4(const std::string& name, const glm::vec4& value) = 0;

		virtual void SetMat2(const std::string& name, const glm::mat2& matrix) = 0;
		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) = 0;

		virtual const std::string& GetName() const = 0;

		static Reference<Shader> CreateFromFile(const std::string& path);
		static Reference<Shader> CreateFromSource(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
	};

}