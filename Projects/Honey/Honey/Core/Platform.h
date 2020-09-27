/**
 * @file Platform.h
 * @brief Platform related stuff.
*/

#pragma once

namespace Honey {

	class Platform {

	public:

		/**
		 * @brief Supported platform APIs
		*/
		enum class API {
			Windows,
			GLFW
		};

		Platform() = delete;
		Platform(const Platform&) = delete;
		Platform& operator =(const Platform&) = delete;

		/**
		 * @brief Initialize Platform.
		 * @return A boolean expressing if the platform was initialized successfully.
		*/
		static bool init();

		/**
		 * @brief Shutdown Platform.
		 * Used to clean up Platform data.
		*/
		static void shutdown();

		/**
		 * @brief Get current Platform API.
		 * @return Current Platform API.
		*/
		static API getAPI();
	};

}
