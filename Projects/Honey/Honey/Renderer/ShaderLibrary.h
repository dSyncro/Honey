#pragma once

#include <unordered_map>

#include "Shader.h"

namespace Honey {

	/**
	 * @brief A shader library contains a single instance of each shader.
	 * It also provides an easy way to access to them by name.
	*/
	class ShaderLibrary {

	public:

		/**
		 * @brief Add shader to library.
		 * @param shader The shader.
		*/
		void add(const Reference<Shader>& shader);

		/**
		 * @brief Add shader to library and assign it a custom name.
		 * @param name Shader name.
		 * @param shader The shader.
		*/
		void add(const std::string& name, const Reference<Shader>& shader);

		/**
		 * @brief Load shader from file.
		 * @param path Shader file path.
		 * @return The shader.
		*/
		Reference<Shader> load(const std::string& path);

		/**
		 * @brief Load shader from file and assign it a custom name.
		 * @param name Shader name.
		 * @param path Shader file path.
		 * @return The shader.
		*/
		Reference<Shader> load(const std::string& name, const std::string& path);

		/**
		 * @brief Get shader from library.
		 * @param name Shader name.
		 * @return The shader if it exists or a null reference.
		*/
		Reference<Shader> get(const std::string& name);

		/**
		 * @brief Check if shader exists in library.
		 * @param name Shader name.
		*/
		bool exists(const std::string& name) const;

	private:

		std::unordered_map<std::string, Reference<Shader>> _shaders;
	};

}
