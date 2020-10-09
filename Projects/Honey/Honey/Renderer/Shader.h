#pragma once

#include <string>

#include <Honey/Core/IBindable.h>
#include <Honey/Core/MemoryManagement.h>
#include <Honey/Math/Matrix/Matrix4x4.h>

#include <glm/glm.hpp>

namespace Honey {

	/**
	 * @brief Shader abstraction.
	*/
	class Shader : public IBindable {

	public:

		virtual ~Shader() = default;

		/**
		 * @brief Set int to shader.
		 * @param name Variable name.
		 * @param value New value.
		*/
		virtual void setInt(const std::string& name, Int value) = 0;

		/**
		 * @brief Set int array to shader.
		 * @param name Variable name.
		 * @param values New values.
		 * @param count Values count.
		*/
		virtual void setIntArray(const std::string& name, Int* values, UInt count) = 0;

		/**
		 * @brief Set float to shader.
		 * @param name Variable name.
		 * @param value New value.
		*/
		virtual void setFloat(const std::string& name, Float value) = 0;

		/**
		 * @brief Set Vector2 to shader.
		 * @param name Variable name.
		 * @param value New value.
		*/
		virtual void setVec2(const std::string& name, const Math::Vector2& value) = 0;

		/**
		 * @brief Set Vector3 to shader.
		 * @param name Variable name.
		 * @param value New value.
		*/
		virtual void setVec3(const std::string& name, const Math::Vector3& value) = 0;

		/**
		 * @brief Set Vector4 to shader.
		 * @param name Variable name.
		 * @param value New value.
		*/
		virtual void setVec4(const std::string& name, const Math::Vector4& value) = 0;

		/**
		 * @brief Set Matrix2x2 to shader.
		 * @param name Variable name.
		 * @param matrix New matrix.
		*/
		virtual void setMat2(const std::string& name, const glm::mat2& matrix) = 0;

		/**
		 * @brief Set Matrix3x3 to shader.
		 * @param name Variable name.
		 * @param matrix New matrix.
		*/
		virtual void setMat3(const std::string& name, const glm::mat3& matrix) = 0;

		/**
		 * @brief Set Matrix4x4 to shader.
		 * @param name Variable name.
		 * @param matrix New matrix.
		*/
		virtual void setMat4(const std::string& name, const Math::Matrix4x4& matrix) = 0;

		/**
		 * @brief Get shader name.
		 * @return Shader name.
		*/
		virtual const std::string& getName() const = 0;

		/**
		 * @brief Create shader from file.
		 * @param path File path.
		 * @return A new memory managed Shader.
		*/
		static Reference<Shader> createFromFile(const std::string& path);

		/**
		 * @brief Create shader directly from source.
		 * @param name Shader name.
		 * @param vertexSource Vertex shader source.
		 * @param fragmentSource Fragment shader source.
		 * @return A new memory managed Shader.
		*/
		static Reference<Shader> createFromSource(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
	};

}
