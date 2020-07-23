#pragma once

#include <entt.hpp>

namespace Honey {

	class Entity;

	class Scene {

	public:

		Scene() = default;
		~Scene() = default;

		Entity CreateEntity(const std::string& tag = "");
		void DeleteEntity(const Entity& entity);

		void OnUpdate();

	private:

		entt::registry _registry;

		friend class Entity;
	};

}