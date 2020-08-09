#pragma once

namespace Honey {

	class Platform {

	public:

		enum class API {
			Windows,
			GLFW
		};

		Platform() = delete;
		Platform(const Platform&) = delete;
		Platform& operator =(const Platform&) = delete;

		static bool Init();
		static void Shutdown();
		static API GetAPI();
	};

}
