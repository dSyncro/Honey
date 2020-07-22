#pragma once

#include <entt.hpp>

namespace Honey {

	class Scene {

	public:

		Scene() = default;
		~Scene() = default;

		entt::entity CreateEntity() { return _registry.create(); }
		entt::registry& GetRegistry() { return _registry; }

		void OnUpdate();

	private:

		entt::registry _registry;
	};

}