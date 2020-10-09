#pragma once

#include <string>
#include <unordered_map>

#include <Honey/Renderer/Shader.h>

#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace Honey {

	/**
	 * @brief OpenGL shader implementation.
	*/
	class OpenGLShader final : public Shader {

	public:

		OpenGLShader(const std::string& name, const std::unordered_map<GLenum, std::string>& shaders);
		
		/**
		 * @brief Create shader from file.
		 * @param path Shader file path.
		 * @return A new memory managed shader.
		*/
		static Reference<OpenGLShader> fromFile(const std::string& path);

		/**
		 * @brief Create shader from source.
		 * @param name Shader name.
		 * @param vertexSource Vertex shader source.
		 * @param fragmentSource Fragment shader source.
		 * @return A new memory managed shader.
		*/
		static Reference<OpenGLShader> fromSource(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);

		virtual ~OpenGLShader();

		/**
		 * @brief Bind shader.
		*/
		virtual void bind() const override;

		/**
		 * @brief Unbind shader.
		*/
		virtual void unbind() const override;

		/**
		 * @brief Check if shader is bound.
		*/
		virtual bool isBound() const override;

		/**
		 * @brief Get shader name.
		 * @return The shader name.
		*/
		virtual const std::string& getName() const override { return _name; }

		/**
		 * @brief Set integer.
		 * @param name Uniform name.
		 * @param value New value.
		*/
		virtual void setInt(const std::string& name, int value) override;

		/**
		 * @brief Set array of integers.
		 * @param name Uniform name.
		 * @param values New values.
		 * @param count Values count.
		*/
		virtual void setIntArray(const std::string& name, int* values, UInt count) override;

		/**
		 * @brief Set float.
		 * @param name Uniform name.
		 * @param value New value.
		*/
		virtual void setFloat(const std::string& name, float value) override;

		/**
		 * @brief Set Vector2.
		 * @param name Uniform name.
		 * @param value New value.
		*/
		virtual void setVec2(const std::string& name, const Math::Vector2& value) override;

		/**
		 * @brief Set Vector3.
		 * @param name Uniform name.
		 * @param value New value.
		*/
		virtual void setVec3(const std::string& name, const Math::Vector3& value) override;

		/**
		 * @brief Set Vector4.
		 * @param name Uniform name.
		 * @param value New value.
		*/
		virtual void setVec4(const std::string& name, const Math::Vector4& value) override;

		/**
		 * @brief Set Matrix2x2.
		 * @param name Uniform name.
		 * @param matrix New matrix.
		*/
		virtual void setMat2(const std::string& name, const glm::mat2& matrix) override;

		/**
		 * @brief Set Matrix3x3.
		 * @param name Uniform name.
		 * @param matrix New matrix.
		*/
		virtual void setMat3(const std::string& name, const glm::mat3& matrix) override;

		/**
		 * @brief Set Matrix4x4.
		 * @param name Uniform name.
		 * @param matrix New matrix.
		*/
		virtual void setMat4(const std::string& name, const Math::Matrix4x4& matrix) override;

	private:

		UInt _rendererID = 0;
		std::string _name;

		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

		static std::string ReadFile(const std::string& path);
		static std::unordered_map<GLenum, std::string> Process(const std::string& source);

		static UInt s_Bound;
	};

}
