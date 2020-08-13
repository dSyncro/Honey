#pragma once

#include <entt.hpp>

#include <Honey/Renderer/Camera/Camera.h>

namespace Honey {

	class Entity;

	struct RenderCameraData {

		Honey::Camera* Camera = nullptr;
		glm::mat4* Transform = nullptr;

		void Reset() noexcept { Camera = nullptr; Transform = nullptr; }

		operator bool() const { return Camera && Transform; }
	};

	class Scene {

	public:

		Scene() = default;
		~Scene() = default;

		Entity CreateEntity(const std::string& name = "Entity", const std::string& tag = "Untagged");
		void DeleteEntity(const Entity& entity);

		void OnUpdate();
		void OnViewportResize(uint32_t width, uint32_t height);

	private:

		entt::registry _registry;
		RenderCameraData _mainCamera;

		friend class Entity;
	};

}
