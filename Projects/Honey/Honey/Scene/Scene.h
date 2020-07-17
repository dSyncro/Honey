#pragma once

#include <entt.hpp>

namespace Honey {

	class Scene {

	public:

		Scene() = default;
		~Scene() = default;

	private:

		entt::registry _registry;
	};

}